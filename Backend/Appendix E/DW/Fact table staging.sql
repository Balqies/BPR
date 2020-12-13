

	use DW_STAGING;
	drop table if EXISTS  TEM_FACT_OEE

	-----------------------

	-- creating TEM_FACT_OEE table 

	create table TEM_FACT_OEE (

	D_ID   int null , -- surrogate key
	M_ID int null ,-- surrogate key
	T_ID    int null , -- surrogate key

	MonitoringPoints_ID int null , -- business key from MonitoringPoints_D
	planedProductionTime int,
	runningTime int,
	actualOutput int,
	thereticalOutput int,
	goodProduct int,
	avaliability_value decimal, 
	performence_value decimal, 
	quality_value decimal, 
	OEE_value decimal, 
	date date,
	time time);
	 CREATE  INDEX "TEM_FACT_OEE_Date" ON "dbo"."TEM_FACT_OEE"("date")
	 CREATE  INDEX "TEM_FACT_OEE_Time" ON "dbo"."TEM_FACT_OEE"("time")
	 GO
	--------------------------------- insert
	insert into TEM_FACT_OEE ( MonitoringPoints_ID,  planedProductionTime, runningTime, actualOutput, thereticalOutput,
	goodProduct, avaliability_value, performence_value, quality_value, date,time)

	select  a.monitoringPointId, a.planedProductionTime ,a.runningTime , b.actualOutput, b.thereticalOutput, c.goodProduct,
	CAST(a.runningTime AS decimal) / CAST(a.planedProductionTime AS decimal) * 100 ,
	CAST(b.actualOutput AS decimal) / CAST(b.thereticalOutput AS decimal) * 100 ,
	CAST(goodProduct AS decimal) / CAST(b.actualOutput AS decimal) * 100,
	
	cast(a.date as date) [date], cast(a.date as time) [time]
 
	from 
	[ProductionMonitoringDB].[dbo].[avaliability]  a join [ProductionMonitoringDB].[dbo].[quality] c
	on a.date = c.date and a.monitoringPointId = c.monitoringPointId
	join [ProductionMonitoringDB].[dbo].[performence] b on b.date = c.date and b.monitoringPointId = c.monitoringPointId

	WHERE DATEPART(hh,a.[date]) >= 15 AND DATEPART(mm,b.[date]) <= 55
	----------------------------------

	select * from TEM_FACT_OEE


	go
	--------------update 
	UPDATE [TEM_FACT_OEE] SET D_ID =(select D_ID from [DW].[dbo].[Dim_Date] where [DW].[dbo].[Dim_Date].Date = TEM_FACT_OEE.date)
	UPDATE [TEM_FACT_OEE] SET T_ID =(select T_ID from [DW].[dbo].[Dim_Time] where [DW].[dbo].[Dim_Time].Time = TEM_FACT_OEE.time)
	UPDATE [TEM_FACT_OEE] SET M_ID =(select M_ID from [DW].[dbo].[Dim_MonitoringPoints] where [DW].[dbo].[Dim_MonitoringPoints].MonitoringPoint_ID = TEM_FACT_OEE.MonitoringPoints_ID)
	UPDATE [TEM_FACT_OEE] SET OEE_value = avaliability_value * performence_value * quality_value / 10000



	-- clean up 





	-- filtering the data and remove NULL values if it exists 
		UPDATE [dbo].[TEM_FACT_OEE] SET planedProductionTime = -4 WHERE planedProductionTime IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET runningTime = -4  WHERE runningTime IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET avaliability_value = -4  WHERE avaliability_value IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET actualOutput = -4 WHERE actualOutput IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET thereticalOutput = -4  WHERE thereticalOutput IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET goodProduct = -4  WHERE goodProduct IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET quality_value = -4 WHERE quality_value IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET performence_value = -4  WHERE performence_value IS NULL;
		 UPDATE [dbo].[TEM_FACT_OEE] SET OEE_value = -4  WHERE OEE_value IS NULL;

	-------------------populate to the fact table

	select * from [TEM_FACT_OEE];


	insert into [DW].[dbo].[Fact_OEE]
		(D_ID,M_ID,T_ID, planedProductionTime,runningTime,actualOutput, thereticalOutput, goodProduct,
		avaliability_value, performence_value,quality_value, OEE_value) 
	select 
		D_ID,M_ID,T_ID, planedProductionTime,runningTime, actualOutput, thereticalOutput, goodProduct,
		avaliability_value, performence_value,quality_value, OEE_value
	from [TEM_FACT_OEE];


	GO
	-- 

	select * from [TEM_FACT_OEE]
	---


	-------------------------------------------------------------------



