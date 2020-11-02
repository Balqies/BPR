CREATE TABLE case-model (
 casemodel-id INT NOT NULL,
 name CHAR(50),
 desctiption CHAR(1000)
);

ALTER TABLE case-model ADD CONSTRAINT PK_case-model PRIMARY KEY (casemodel-id);


CREATE TABLE customer (
 custmer-id INT NOT NULL,
 first-name CHAR(50),
 last-name CHAR(50),
 Email CHAR(70),
 mobile INT,
 address CHAR(100),
 dateOfCreation DATE
);

ALTER TABLE customer ADD CONSTRAINT PK_customer PRIMARY KEY (custmer-id);


CREATE TABLE mobile-type (
 mobileType-id INT NOT NULL,
 type CHAR(50)
);

ALTER TABLE mobile-type ADD CONSTRAINT PK_mobile-type PRIMARY KEY (mobileType-id);


CREATE TABLE monitoring-point (
 monitoringPoint-id INT NOT NULL,
 name VARCHAR(50)
);

ALTER TABLE monitoring-point ADD CONSTRAINT PK_monitoring-point PRIMARY KEY (monitoringPoint-id);


CREATE TABLE Order (
 order-id INT NOT NULL,
 custmer-id INT NOT NULL,
 order-date DATE
);

ALTER TABLE Order ADD CONSTRAINT PK_Order PRIMARY KEY (order-id,custmer-id);


CREATE TABLE order_line (
 order-id INT NOT NULL,
 custmer-id INT NOT NULL,
 mobileType-id INT NOT NULL,
 casemodel-id INT NOT NULL,
 amount DATE
);

ALTER TABLE order_line ADD CONSTRAINT PK_order_line PRIMARY KEY (order-id,custmer-id,mobileType-id,casemodel-id);


CREATE TABLE performence (
 performence-id INT NOT NULL,
 monitoringPoint-id INT NOT NULL,
 actualOutput INT,
 thereticalOutput INT,
 date TIMESTAMP(10)
);

ALTER TABLE performence ADD CONSTRAINT PK_performence PRIMARY KEY (performence-id,monitoringPoint-id);


CREATE TABLE quality (
 quality-id INT NOT NULL,
 monitoringPoint-id INT NOT NULL,
 goodProduct INT,
 totalProduct CHAR(10),
 date TIMESTAMP(10)
);

ALTER TABLE quality ADD CONSTRAINT PK_quality PRIMARY KEY (quality-id,monitoringPoint-id);


CREATE TABLE avaliability (
 avaliability-id INT NOT NULL,
 monitoringPoint-id INT NOT NULL,
 planedProductionTime INT,
 runningTime INT,
 date TIMESTAMP(30)
);

ALTER TABLE avaliability ADD CONSTRAINT PK_avaliability PRIMARY KEY (avaliability-id,monitoringPoint-id);


ALTER TABLE Order ADD CONSTRAINT FK_Order_0 FOREIGN KEY (custmer-id) REFERENCES customer (custmer-id);


ALTER TABLE order_line ADD CONSTRAINT FK_order_line_0 FOREIGN KEY (order-id,custmer-id) REFERENCES Order (order-id,custmer-id);
ALTER TABLE order_line ADD CONSTRAINT FK_order_line_1 FOREIGN KEY (mobileType-id) REFERENCES mobile-type (mobileType-id);
ALTER TABLE order_line ADD CONSTRAINT FK_order_line_2 FOREIGN KEY (casemodel-id) REFERENCES case-model (casemodel-id);


ALTER TABLE performence ADD CONSTRAINT FK_performence_0 FOREIGN KEY (monitoringPoint-id) REFERENCES monitoring-point (monitoringPoint-id);


ALTER TABLE quality ADD CONSTRAINT FK_quality_0 FOREIGN KEY (monitoringPoint-id) REFERENCES monitoring-point (monitoringPoint-id);


ALTER TABLE avaliability ADD CONSTRAINT FK_avaliability_0 FOREIGN KEY (monitoringPoint-id) REFERENCES monitoring-point (monitoringPoint-id);


