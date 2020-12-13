
use DW_STAGING;

drop table if exists changedMonitoringPoints ;

go
-- 1. Create changed TABLE

create table changedMonitoringPoints(id int,"ValidFrom" nvarchar(20)  null DEFAULT '11/01/2020',
"Validto" nvarchar(20)  null DEFAULT '01/01/2099'
);

go
--- 2. INSERT INTO changed TABLE
Insert into [DW_STAGING].[dbo].[changedMonitoringPoints]
(
id
)

(
--- today
select  
 id
	  FROM ProductionMonitoringDB.dbo.MonitoringPoint
)

EXCEPT
(
--- yesterday

select MonitoringPoint_ID
from 
[DW].[dbo].[Dim_MonitoringPoints] 

)

EXCEPT 
(

select  
 id
	  FROM ProductionMonitoringDB.dbo.MonitoringPoint 

where id NOT In (SELECT  
MonitoringPoint_ID
FROM
[DW].[dbo].[Dim_MonitoringPoints] )

)


go 



use DW;

--- 2. Update exsisting row in dimension table
 update Dim_MonitoringPoints 
 SET ValidTo = '11/12/2020'   --- last Updated
WHERE MonitoringPoint_ID IN
(SELECT MonitoringPoint_ID
FROM [DW_STAGING].[dbo].[changedMonitoringPoints]

)


--- 3. Insert new row in dimension table
 UPDATE [DW_STAGING].[dbo].[changedMonitoringPoints] SET id = -4 WHERE id IS NULL;

 insert into [DW].[dbo].[Dim_MonitoringPoints] 
 (
MonitoringPoint_ID, ValidFrom,Validto
 )
 select 

id , '11/13/2019', '11/13/2019' ---- last updated + 1

 FROM [DW_STAGING].[dbo].[changedMonitoringPoints] 

 go;

 SELECT * FROM [DW_STAGING].[dbo].[changedMonitoringPoints]
 GO


 Delete From [DW_STAGING].[dbo].[changedMonitoringPoints]

