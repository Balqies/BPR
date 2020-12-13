use DW;

 go 

 update [DW].[dbo].[Dim_MonitoringPoints]  
 set Validto = '11/20/2019'  --- last Updated

 where MonitoringPoint_ID in (
 --- yesterday
(select MonitoringPoint_ID
from [DW].[dbo].[Dim_MonitoringPoints]
 ) 

 EXCEPT 
 (
 --- today
select [id]
from [ProductionMonitoringDB].[dbo].[MonitoringPoint]

)
)