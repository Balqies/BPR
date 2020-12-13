	use DW

	Drop table if exists Fact_OEE
	Drop table if exists Dim_Date
	Drop table if exists Dim_Time
	Drop table if exists Dim_MonitoringPoints


	-- creating the Date dimension.

	 go

	CREATE TABLE "Dim_Date"
	(
	D_ID int identity (1,1) not null
	,Date DATETIME not null
	, Day nvarchar(50) not null
	, Month nvarchar(50) not null
	, Year nvarchar(50) not null
	,constraint "PK_Date_ID" primary key(
			"D_ID"
	)
	)
	go
	DECLARE @StartDate DATETIME
	DECLARE @EndDate DATETIME
	SET @StartDate = '2020-11-01'
	SET @EndDate = DATEADD(m, 3,
	@StartDate)
	WHILE @StartDate <= @EndDate
	BEGIN
	INSERT INTO [Dim_Date]
	(
	Date
	,Day
	,Month
	,Year
	)
	SELECT
	@StartDate
	,DATENAME(weekday,@startDate)
	,DATENAME(month, @StartDate )
	,DATENAME(YEAR, @StartDate )
	SET @StartDate = DATEADD(dd, 1, @StartDate)
	END
	 go
	select * from Dim_Date

	go
   
	-- creating the time dimension.
	  CREATE TABLE "Dim_Time"
	(
	 T_ID int identity (1,1) not null
	, Time  TIME not null
	, hour tinyint not null
	, Minute tinyint not null
	, Second tinyint not null
	,constraint "PK_Dim_Time" primary key(
			"T_ID"
	)
	)
	go
	DECLARE @Hour TIME
	DECLARE @EndHour TIME
	SET @Hour = '08:00:01'
	SET @EndHour = DATEADD(second,28800,@Hour)
	WHILE (@Hour <= @EndHour)
	BEGIN
	INSERT INTO [Dim_Time]
	(
	Time,
	hour,
	Minute,
	Second
	)
	SELECT
	@Hour
	,DATENAME(HOUR,@Hour)
	,DATENAME(minute,@Hour)
	,DATENAME(second, @Hour )
	SET @Hour = DATEADD(second,1, @Hour)
	END

	go
	select * from Dim_Time

	-- creating the monitoringPoints dimension. 

	create table Dim_MonitoringPoints(
	M_ID  int  IDENTITY, -- surrogate key
	MonitoringPoint_ID  int, -- busniness key 

	"ValidFrom" nvarchar(20) not null DEFAULT '01/11/2020',
	"Validto" nvarchar(20) not null DEFAULT '01/05/2099'

	primary key (M_ID)
	);
	 CREATE  INDEX "MonitoringPoint_ID" ON "DW"."dbo"."Dim_MonitoringPoints"("M_ID")
	 GO
	 select * from Dim_MonitoringPoints
	 go

	-- craeting OEE fact table
	create table Fact_OEE (
	D_ID   int,-- surrogate key
	M_ID int,-- surrogate key
	T_ID    int,-- surrogate key
	planedProductionTime int,
	runningTime int,
	actualOutput int,
	thereticalOutput int,
	goodProduct int,
	avaliability_value decimal, 
	performence_value decimal, 
	quality_value decimal, 
	OEE_value decimal, 
	primary key (D_ID,M_ID, T_ID),
	foreign key ("D_ID")  references [DW].[dbo].[Dim_Date] ( "D_ID" ),
	foreign key ("M_ID") references [DW].[dbo].[Dim_MonitoringPoints] ( "M_ID" ),
	foreign key ("T_ID") references [DW].[dbo].[Dim_Time] ( "T_ID" ) 

	);

	go 
	select * from Fact_OEE

	go

	