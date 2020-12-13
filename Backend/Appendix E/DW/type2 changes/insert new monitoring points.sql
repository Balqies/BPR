use DW;

insert into [DW].[dbo].[Dim_MonitoringPoints]  
(

MonitoringPoint_ID,  ValidFrom, Validto ) 
select  
  id, '11/01/2020', '01/01/2099' -- LAST UPDATE +1
	  FROM ProductionMonitoringDB.dbo.MonitoringPoint 


where id in 
((
--- today
select [id]

from [ProductionMonitoringDB].[dbo].[MonitoringPoint] 
)

EXCEPT 

--- yesterday

 ( select MonitoringPoint_ID from [DW].[dbo].[Dim_MonitoringPoints]  
 )
 )
