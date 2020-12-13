	USE [ProductionMonitoringDB]
	GO


-------------------------------------------------------Customer table ------------------------------------------------------------------------------------------------------


	CREATE TABLE [dbo].[Customer](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[firstName] [varchar](50) NOT NULL,
		[lastName] [varchar](50) NOT NULL,
		[email] [varchar](100) NOT NULL,
		[mobile] [int] NOT NULL,
		[city] [varchar](50) NOT NULL,
		[dateOfCreation] [date] NOT NULL,
		CONSTRAINT [PK_customer] PRIMARY KEY ( id)
		)
	GO
	GO

----------------------------------------------------------Order table ----------------------------------------------------------------------------

	CREATE TABLE [dbo].[order](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[customerId] [int] NOT NULL,
		[date] [date] NOT NULL,
		CONSTRAINT [PK_order] PRIMARY KEY ( id)
		)

	GO

	ALTER TABLE [dbo].[order]  WITH CHECK ADD  CONSTRAINT [FK_order_customer] FOREIGN KEY([customerId])
	REFERENCES [dbo].[Customer] ([id])
	GO

	ALTER TABLE [dbo].[order] CHECK CONSTRAINT [FK_order_customer]
	GO



----------------------------------------------------------Mobile type table-------------------------------------------------------------------

	CREATE TABLE [dbo].[MobileType](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[name] [varchar](50) NOT NULL,
		CONSTRAINT [PK_MobileType] PRIMARY KEY ( id)
 
		)
	GO

---------------------------------------------------------- Case Model table -------------------------------------------------------------------


	CREATE TABLE [dbo].[CaseModel](
		[id] [int] IDENTITY(100,1) NOT NULL,
		[description] [varchar](100) NOT NULL,
		CONSTRAINT [PK_case-model] PRIMARY KEY ( id)
 
		)
	GO

---------------------------------------------------------- Order Line Table -------------------------------------------------------------------


	CREATE TABLE [dbo].[orderLine](
		[orderId] [int] NOT NULL,
		[caseModelId] [int] NOT NULL,
		[mobileTypeId] [int] NOT NULL,
		[amount] [int] NOT NULL
	) ON [PRIMARY]
	GO

	ALTER TABLE [dbo].[orderLine]  WITH CHECK ADD  CONSTRAINT [FK_orderLine_CaseModel] FOREIGN KEY([caseModelId])
	REFERENCES [dbo].[CaseModel] ([id])
	GO

	ALTER TABLE [dbo].[orderLine] CHECK CONSTRAINT [FK_orderLine_CaseModel]
	GO

	ALTER TABLE [dbo].[orderLine]  WITH CHECK ADD  CONSTRAINT [FK_orderLine_MobileType] FOREIGN KEY([mobileTypeId])
	REFERENCES [dbo].[MobileType] ([id])
	GO

	ALTER TABLE [dbo].[orderLine] CHECK CONSTRAINT [FK_orderLine_MobileType]
	GO

	ALTER TABLE [dbo].[orderLine]  WITH CHECK ADD  CONSTRAINT [FK_orderLine_order] FOREIGN KEY([orderId])
	REFERENCES [dbo].[order] ([id])
	GO

	ALTER TABLE [dbo].[orderLine] CHECK CONSTRAINT [FK_orderLine_order]
	GO
----------------------------------------------------------Monitoring Points Table ------------------------------------------------------------------------------------------------------


	CREATE TABLE [dbo].[MonitoringPoint](
		[id] [int] NOT NULL,
		CONSTRAINT [PK_monitoirng-point] PRIMARY KEY ( id)
 
		)
	GO

----------------------------------------------------------Avaliability table ------------------------------------------------------------------------------------------------------


	CREATE TABLE [dbo].[avaliability](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[monitoringPointId] [int] NOT NULL,
		[planedProductionTime] [int] NOT NULL,
		[runningTime] [int] NOT NULL,
		[date] [datetime] NOT NULL,
		CONSTRAINT [PK_avaliability] PRIMARY KEY ( id)
 
		)
	GO

	ALTER TABLE [dbo].[avaliability]  WITH CHECK ADD  CONSTRAINT [FK_avaliability_monitoirng-point] FOREIGN KEY([monitoringPointId])
	REFERENCES [dbo].[MonitoringPoint] ([id])
	GO

	ALTER TABLE [dbo].[avaliability] CHECK CONSTRAINT [FK_avaliability_monitoirng-point]
	GO


------------------------------------------------------------------Performence Table-------------------------------------------------------------------------------------------------------------------------------------------------

	CREATE TABLE [dbo].[performence](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[monitoringPointId] [int] NOT NULL,
		[actualOutput] [int] NOT NULL,
		[thereticalOutput] [int] NOT NULL,
		[date] [datetime] NOT NULL,
		CONSTRAINT [PK_performence] PRIMARY KEY ( id)
 
		)
	GO

	ALTER TABLE [dbo].[performence]  WITH CHECK ADD  CONSTRAINT [FK_performence_monitoirng-point] FOREIGN KEY([monitoringPointId])
	REFERENCES [dbo].[MonitoringPoint] ([id])
	GO

	ALTER TABLE [dbo].[performence] CHECK CONSTRAINT [FK_performence_monitoirng-point]
	GO

------------------------------------------------------------------Quality talbe -----------------------------------------------------------

	CREATE TABLE [dbo].[quality](
		[id] [int] IDENTITY(1,1) NOT NULL,
		[monitoringPointId] [int] NOT NULL,
		[goodProduct] [int] NOT NULL,
		[totalProduct] [int] NOT NULL,
		[date] [datetime] NOT NULL,
		CONSTRAINT [PK_quality] PRIMARY KEY ( id)
 
		)
	GO

	ALTER TABLE [dbo].[quality]  WITH CHECK ADD  CONSTRAINT [FK_quality_monitoirng-point] FOREIGN KEY([monitoringPointId])
	REFERENCES [dbo].[MonitoringPoint] ([id])
	GO

	ALTER TABLE [dbo].[quality] CHECK CONSTRAINT [FK_quality_monitoirng-point]
	GO


