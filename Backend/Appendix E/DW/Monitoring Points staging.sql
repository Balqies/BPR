Use DW_STAGING
Drop table if exists MonitoringPoint_D_STAGE

go 
 --creating the MonitoringPoint staging table that hat the same fiedls as the Dim_Monitoring Points 

create table MonitoringPoint_D_STAGE (
M_ID   int identity ,
MonitoringPoint_ID  int, 

);
  CREATE  INDEX "MonitoringPoint_ID" ON "dbo".MonitoringPoint_D_STAGE("MonitoringPoint_ID")
 

  -- getting the values from the  sousce code and inserting them in the staging table fields 

insert into MonitoringPoint_D_STAGE( MonitoringPoint_ID) select  
id
	  FROM ProductionMonitoringDB.dbo.MonitoringPoint

 select * from MonitoringPoint_D_STAGE;

  


   -- delete duplicate rows
  
	   WITH MonitoringPoint_STAGE AS
	(SELECT *,ROW_NUMBER() OVER (PARTITION BY MonitoringPoint_ID ORDER BY  MonitoringPoint_ID) AS RowNumber
	FROM MonitoringPoint_D_STAGE )
	DELETE  FROM MonitoringPoint_STAGE WHERE RowNumber > 1
 
 GO
 SELECT * FROM MonitoringPoint_D_STAGE

 --insert data into the dimension 
 insert into [DW].[dbo].[Dim_MonitoringPoints] (
     [MonitoringPoint_ID]) select
     MonitoringPoint_ID from [DW].[dbo].[MonitoringPoint_D_STAGE];

      select * from [DW].[dbo].[Dim_MonitoringPoints];
