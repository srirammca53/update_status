-- MySQL dump 10.13  Distrib 5.1.41, for debian-linux-gnu (i486)
--
-- Host: localhost    Database: Nyros
-- ------------------------------------------------------
-- Server version	5.1.41-3ubuntu12.10

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ROR_team`
--

DROP TABLE IF EXISTS `ROR_team`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ROR_team` (
  `Emp_id` int(11) NOT NULL AUTO_INCREMENT,
  `Emp_name` varchar(50) NOT NULL,
  `Emp_age` int(2) NOT NULL,
  `Emp_joined` date DEFAULT NULL,
  `Emp_exp` int(11) NOT NULL,
  PRIMARY KEY (`Emp_id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ROR_team`
--

LOCK TABLES `ROR_team` WRITE;
/*!40000 ALTER TABLE `ROR_team` DISABLE KEYS */;
INSERT INTO `ROR_team` VALUES (1,'sree',24,'2011-04-18',0),(2,'Prabhu',28,'2006-04-12',5),(3,'shruthi',24,'2010-06-12',1),(4,'pavan',29,'2006-10-12',5),(5,'Shanthi',29,'2009-10-02',3);
/*!40000 ALTER TABLE `ROR_team` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dotnet_team`
--

DROP TABLE IF EXISTS `dotnet_team`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dotnet_team` (
  `Emp_id` int(11) NOT NULL AUTO_INCREMENT,
  `Emp_name` varchar(50) NOT NULL,
  `Emp_age` int(2) NOT NULL,
  `Emp_joined` date DEFAULT NULL,
  `Emp_exp` int(11) NOT NULL,
  PRIMARY KEY (`Emp_id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dotnet_team`
--

LOCK TABLES `dotnet_team` WRITE;
/*!40000 ALTER TABLE `dotnet_team` DISABLE KEYS */;
INSERT INTO `dotnet_team` VALUES (1,'Ram',24,'2011-04-12',0),(2,'Ravindra',28,'2006-04-03',5),(3,'Tarun',25,'2010-04-05',3),(4,'Indhu',28,'2007-04-05',4);
/*!40000 ALTER TABLE `dotnet_team` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `php_team`
--

DROP TABLE IF EXISTS `php_team`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `php_team` (
  `Emp_id` int(11) NOT NULL AUTO_INCREMENT,
  `Emp_name` varchar(50) NOT NULL,
  `Emp_age` int(2) NOT NULL,
  `Emp_joined` date DEFAULT NULL,
  `Emp_exp` int(11) NOT NULL,
  PRIMARY KEY (`Emp_id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `php_team`
--

LOCK TABLES `php_team` WRITE;
/*!40000 ALTER TABLE `php_team` DISABLE KEYS */;
INSERT INTO `php_team` VALUES (1,'kiran',24,'2010-05-06',1),(2,'Ravi',28,'2007-10-10',4),(3,'raghu',27,'2008-03-11',3),(4,'priya',27,'2006-06-12',5),(5,'Nandhini',28,'2006-08-12',5);
/*!40000 ALTER TABLE `php_team` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-06-02  8:33:02
