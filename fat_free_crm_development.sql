-- phpMyAdmin SQL Dump
-- version 2.8.2
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Jun 02, 2011 at 09:46 AM
-- Server version: 5.0.22
-- PHP Version: 5.1.4
-- 
-- Database: `fat_free_crm_development`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `account_contacts`
-- 

CREATE TABLE `account_contacts` (
  `id` int(11) NOT NULL auto_increment,
  `account_id` int(11) default NULL,
  `contact_id` int(11) default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `account_contacts`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `account_opportunities`
-- 

CREATE TABLE `account_opportunities` (
  `id` int(11) NOT NULL auto_increment,
  `account_id` int(11) default NULL,
  `opportunity_id` int(11) default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `account_opportunities`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `account_types`
-- 

CREATE TABLE `account_types` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(36) collate utf8_unicode_ci default NULL,
  `title` varchar(36) collate utf8_unicode_ci default NULL,
  `price` int(11) default '0',
  `teams_allowed` int(11) default '0',
  `storage_allowed` int(11) default '0',
  `contacts_allowed` int(11) default '0',
  `emails_allowed` int(11) default '0',
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=6 ;

-- 
-- Dumping data for table `account_types`
-- 

INSERT INTO `account_types` VALUES (1, 'account type 1', 'free account', 0, 0, 0, 250, 0, '2010-09-13 15:44:43', '2010-09-13 15:44:43');
INSERT INTO `account_types` VALUES (2, 'account type 2', 'payed account 2', 24, 6, 3, 2000, 2, '2010-09-13 15:44:43', '2010-09-13 15:44:43');
INSERT INTO `account_types` VALUES (3, 'account type 3', 'payed account 3', 49, 10, 5, 5000, 5, '2010-09-13 15:44:43', '2010-09-13 15:44:43');
INSERT INTO `account_types` VALUES (4, 'account type 4', 'payed account 3', 99, 15, 20, 10000, 10, '2010-09-13 15:44:43', '2010-09-13 15:44:43');
INSERT INTO `account_types` VALUES (5, 'account type 5', 'payed account 5', 149, 100, 40, 25000, 15, '2010-09-13 15:44:43', '2010-09-13 15:44:43');

-- --------------------------------------------------------

-- 
-- Table structure for table `accounts`
-- 

CREATE TABLE `accounts` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `access` varchar(8) collate utf8_unicode_ci default 'Private',
  `website` varchar(64) collate utf8_unicode_ci default NULL,
  `toll_free_phone` varchar(32) collate utf8_unicode_ci default NULL,
  `phone` varchar(32) collate utf8_unicode_ci default NULL,
  `fax` varchar(32) collate utf8_unicode_ci default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `email` varchar(64) collate utf8_unicode_ci default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  `vendor_type_id` int(11) default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_accounts_on_user_id_and_name_and_deleted_at` (`user_id`,`name`,`deleted_at`),
  KEY `index_accounts_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=25 ;

-- 
-- Dumping data for table `accounts`
-- 

INSERT INTO `accounts` VALUES (1, 1, NULL, 'mahesh', 'Public', 'test_contact', 'test_contact', 'dasd', 'adasd', '2010-09-17 03:25:04', '2010-09-15 10:09:20', '2010-09-15 13:12:24', 'test_contact@test_contact.test_contact', NULL, 5);
INSERT INTO `accounts` VALUES (2, 1, NULL, 'gdfg', 'Public', 'gdfgdf', 'dfg', 'dfg', 'dfgdf', '2010-09-17 03:25:27', '2010-09-15 10:10:44', '2010-09-15 13:12:14', 'gdfgd@das.mju', NULL, 4);
INSERT INTO `accounts` VALUES (3, 1, NULL, 'vn', 'Public', 'y', 'ytr', 'yrt', 'yrty', '2010-09-17 03:25:08', '2010-09-15 10:29:02', '2010-09-15 13:12:48', 'ytryrttry@xfxf.,ki', NULL, 5);
INSERT INTO `accounts` VALUES (4, 1, NULL, 'dfgd', 'Team', 'test_contact', 'dfgd', 'dfgd', 'adasd', '2010-09-17 03:24:54', '2010-09-15 10:32:17', '2010-09-17 03:04:16', 'test_contact@test_contact.test_contact', NULL, 1);
INSERT INTO `accounts` VALUES (5, 1, NULL, 'dsfsd', 'Public', 'test_contact', 'test_contact', 'dasd', 'adasd', '2010-09-17 03:24:58', '2010-09-15 10:33:27', '2010-09-15 13:10:32', 'test_contact@test_contact.test_contact', NULL, 5);
INSERT INTO `accounts` VALUES (6, 1, NULL, 'dgdf', 'Public', 'test_contact', 'test_contact', 'dasd', 'adasd', '2010-09-17 03:24:56', '2010-09-15 10:34:53', '2010-09-15 13:10:21', 'test_contact@test_contact.test_contact', NULL, 3);
INSERT INTO `accounts` VALUES (7, 1, NULL, 'maheshxcvxv', 'Public', 'xcvxc', 'vxcv', 'xcvx', 'cvxc', '2010-09-17 03:25:28', '2010-09-15 10:35:35', '2010-09-15 13:12:33', 'test_contact@test_contact.test_contact', NULL, 3);
INSERT INTO `accounts` VALUES (8, 1, NULL, 'sdfds', 'Public', 'fdsf', 'sdfs', 'fds', 'dsfs', '2010-09-17 03:25:05', '2010-09-15 13:02:24', '2010-09-15 13:02:24', 'dsfdsf', NULL, 4);
INSERT INTO `accounts` VALUES (9, 1, 2, 'asdasd', 'Team', 'asdas', 'asd', 'asd', 'sdasd', '2010-09-17 03:24:43', '2010-09-16 11:03:32', '2010-09-16 12:10:40', 'dasd', NULL, 5);
INSERT INTO `accounts` VALUES (10, 1, 2, 'werwe', 'Team', 'rwe', 'wewe', 'rwe', 'rwerwe', '2010-09-17 03:25:10', '2010-09-16 11:06:57', '2010-09-16 11:06:57', 'werwe', NULL, 4);
INSERT INTO `accounts` VALUES (11, 1, 2, 'fdsfsd', 'Team', 'fds', 'sd', 'fsdf', 'dsds', '2010-09-17 03:25:01', '2010-09-16 11:47:40', '2010-09-16 11:47:40', 'fdsf', NULL, 3);
INSERT INTO `accounts` VALUES (12, 1, 2, 'asdasdddd', 'Team', 'asdas', 'dfg', 'asd', 'czxc', '2010-09-17 03:24:39', '2010-09-16 11:55:49', '2010-09-16 11:55:49', 'dasd', NULL, 5);
INSERT INTO `accounts` VALUES (13, 1, 2, 'dsfdsf', 'Team', 'fds', 'sdf', 'sdf', 'dsfds', '2010-09-17 03:25:21', '2010-09-16 12:30:53', '2010-09-16 12:30:53', 'fdsf', NULL, 4);
INSERT INTO `accounts` VALUES (14, 1, 2, 'vxcv', 'Team', 'xcv', 'cv', 'xcvx', 'cvxcv', '2010-09-17 03:25:30', '2010-09-16 12:35:58', '2010-09-16 12:36:55', 'xcvxcv', NULL, 6);
INSERT INTO `accounts` VALUES (15, 1, 2, 'ytrytr', 'Team', 'try', 'try', 'try', 'trytry', '2010-09-17 03:25:11', '2010-09-16 13:14:12', '2010-09-16 13:14:47', 'trytr', NULL, 4);
INSERT INTO `accounts` VALUES (16, 1, 2, 'dsfsdsdfsd', 'Shared', 'dsf', 'sdfs', 'df', 'sdfdsf', '2010-09-17 03:25:00', '2010-09-16 13:36:01', '2010-09-16 13:36:23', 'dsfds', NULL, 4);
INSERT INTO `accounts` VALUES (17, 1, 2, 'rtutr', 'Team', 'tru', 'rtu', 'rtu', 'tru', '2010-09-17 07:09:47', '2010-09-17 03:27:56', '2010-09-17 03:27:56', 'trutr', NULL, 2);
INSERT INTO `accounts` VALUES (18, 1, NULL, 'aaaa', 'Team', '', '', '', '', '2010-09-17 07:09:44', '2010-09-17 03:32:31', '2010-09-17 03:32:31', '', NULL, 8);
INSERT INTO `accounts` VALUES (19, 1, 2, 'team selected chnage to user remove both', 'Private', 'dasd', 'asdas', 'dasd', 'asd', '2010-09-17 07:09:34', '2010-09-17 03:52:24', '2010-09-17 03:55:02', 'dasda', NULL, 5);
INSERT INTO `accounts` VALUES (20, 1, 2, 'nagesh', 'Team', 'as', 'as', 'das', 'dasd', '2010-09-17 07:09:51', '2010-09-17 04:24:08', '2010-09-17 04:26:23', 'dasd', NULL, 3);
INSERT INTO `accounts` VALUES (21, 1, 2, 'mahesh', 'Shared', 'asd', 'asd', 'as', 'dasd', '2010-09-17 07:09:45', '2010-09-17 04:24:37', '2010-09-17 04:25:17', 'asd', NULL, 2);
INSERT INTO `accounts` VALUES (22, 1, NULL, 'aaa', 'Private', '', '', '', '', '2010-09-17 07:09:42', '2010-09-17 05:49:08', '2010-09-17 05:49:08', '', NULL, 11);
INSERT INTO `accounts` VALUES (23, 1, NULL, 'sss', 'Private', '', '', '', '', '2010-09-17 07:09:38', '2010-09-17 05:50:09', '2010-09-17 05:50:09', '', NULL, 13);
INSERT INTO `accounts` VALUES (24, 1, NULL, 'Vendor 1', 'Public', 'Vendor 1', 'Vendor 1', 'Vendor 1', 'Vendor 1', NULL, '2010-09-17 07:10:43', '2010-09-17 08:38:14', 'Vendor 1', NULL, 1);

-- --------------------------------------------------------

-- 
-- Table structure for table `activities`
-- 

CREATE TABLE `activities` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `subject_id` int(11) default NULL,
  `subject_type` varchar(255) collate utf8_unicode_ci default NULL,
  `action` varchar(32) collate utf8_unicode_ci default 'created',
  `info` varchar(255) collate utf8_unicode_ci default '',
  `private` tinyint(1) default '0',
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_activities_on_user_id` (`user_id`),
  KEY `index_activities_on_created_at` (`created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=101 ;

-- 
-- Dumping data for table `activities`
-- 

INSERT INTO `activities` VALUES (1, 1, 1, 'Account', 'created', 'mahesh', 0, '2010-09-15 10:09:20', '2010-09-15 10:09:20');
INSERT INTO `activities` VALUES (3, 1, 2, 'Account', 'created', 'gdfg', 0, '2010-09-15 10:10:44', '2010-09-15 10:10:44');
INSERT INTO `activities` VALUES (5, 1, 3, 'Account', 'created', 'vn', 0, '2010-09-15 10:29:02', '2010-09-15 10:29:02');
INSERT INTO `activities` VALUES (7, 1, 4, 'Account', 'created', 'dfgd', 0, '2010-09-15 10:32:17', '2010-09-15 10:32:17');
INSERT INTO `activities` VALUES (9, 1, 5, 'Account', 'created', 'dsfsd', 0, '2010-09-15 10:33:27', '2010-09-15 10:33:27');
INSERT INTO `activities` VALUES (11, 1, 6, 'Account', 'created', 'dgdf', 0, '2010-09-15 10:34:53', '2010-09-15 10:34:53');
INSERT INTO `activities` VALUES (13, 1, 7, 'Account', 'created', 'maheshxcvxv', 0, '2010-09-15 10:35:35', '2010-09-15 10:35:35');
INSERT INTO `activities` VALUES (15, 1, 1, 'Contact', 'created', 'asda asdasd', 0, '2010-09-15 11:27:04', '2010-09-15 11:27:04');
INSERT INTO `activities` VALUES (17, 1, 7, 'Account', 'updated', 'maheshxcvxv', 0, '2010-09-15 11:41:04', '2010-09-15 11:41:04');
INSERT INTO `activities` VALUES (18, 1, 4, 'Account', 'updated', 'dfgd', 0, '2010-09-15 11:51:50', '2010-09-15 11:51:50');
INSERT INTO `activities` VALUES (19, 1, 8, 'Account', 'created', 'sdfds', 0, '2010-09-15 13:02:24', '2010-09-15 13:02:24');
INSERT INTO `activities` VALUES (21, 1, 4, 'Account', 'updated', 'dfgd', 0, '2010-09-15 13:10:11', '2010-09-15 13:10:11');
INSERT INTO `activities` VALUES (22, 1, 6, 'Account', 'updated', 'dgdf', 0, '2010-09-15 13:10:21', '2010-09-15 13:10:21');
INSERT INTO `activities` VALUES (23, 1, 5, 'Account', 'updated', 'dsfsd', 0, '2010-09-15 13:10:32', '2010-09-15 13:10:32');
INSERT INTO `activities` VALUES (24, 1, 2, 'Account', 'updated', 'gdfg', 0, '2010-09-15 13:12:14', '2010-09-15 13:12:14');
INSERT INTO `activities` VALUES (25, 1, 1, 'Account', 'updated', 'mahesh', 0, '2010-09-15 13:12:24', '2010-09-15 13:12:24');
INSERT INTO `activities` VALUES (26, 1, 7, 'Account', 'updated', 'maheshxcvxv', 0, '2010-09-15 13:12:33', '2010-09-15 13:12:33');
INSERT INTO `activities` VALUES (27, 1, 3, 'Account', 'updated', 'vn', 0, '2010-09-15 13:12:48', '2010-09-15 13:12:48');
INSERT INTO `activities` VALUES (28, 1, 9, 'Account', 'created', 'asdasd', 0, '2010-09-16 11:03:32', '2010-09-16 11:03:32');
INSERT INTO `activities` VALUES (30, 1, 10, 'Account', 'created', 'werwe', 0, '2010-09-16 11:06:57', '2010-09-16 11:06:57');
INSERT INTO `activities` VALUES (32, 1, 11, 'Account', 'created', 'fdsfsd', 0, '2010-09-16 11:47:40', '2010-09-16 11:47:40');
INSERT INTO `activities` VALUES (34, 1, 12, 'Account', 'created', 'asdasdddd', 0, '2010-09-16 11:55:49', '2010-09-16 11:55:49');
INSERT INTO `activities` VALUES (36, 1, 9, 'Account', 'updated', 'asdasd', 0, '2010-09-16 12:10:40', '2010-09-16 12:10:40');
INSERT INTO `activities` VALUES (37, 1, 13, 'Account', 'created', 'dsfdsf', 0, '2010-09-16 12:30:53', '2010-09-16 12:30:53');
INSERT INTO `activities` VALUES (39, 1, 14, 'Account', 'created', 'vxcv', 0, '2010-09-16 12:35:58', '2010-09-16 12:35:58');
INSERT INTO `activities` VALUES (41, 1, 14, 'Account', 'updated', 'vxcv', 0, '2010-09-16 12:36:56', '2010-09-16 12:36:56');
INSERT INTO `activities` VALUES (42, 1, 9, 'Account', 'updated', 'asdasd', 0, '2010-09-16 12:47:54', '2010-09-16 12:47:54');
INSERT INTO `activities` VALUES (43, 1, 15, 'Account', 'created', 'ytrytr', 0, '2010-09-16 13:14:12', '2010-09-16 13:14:12');
INSERT INTO `activities` VALUES (45, 1, 15, 'Account', 'updated', 'ytrytr', 0, '2010-09-16 13:14:47', '2010-09-16 13:14:47');
INSERT INTO `activities` VALUES (46, 1, 16, 'Account', 'created', 'dsfsdsdfsd', 0, '2010-09-16 13:36:02', '2010-09-16 13:36:02');
INSERT INTO `activities` VALUES (48, 1, 16, 'Account', 'updated', 'dsfsdsdfsd', 0, '2010-09-16 13:36:23', '2010-09-16 13:36:23');
INSERT INTO `activities` VALUES (49, 1, 12, 'Account', 'updated', 'asdasdddd', 0, '2010-09-17 03:03:25', '2010-09-17 03:03:25');
INSERT INTO `activities` VALUES (50, 1, 4, 'Account', 'updated', 'dfgd', 0, '2010-09-17 03:04:16', '2010-09-17 03:04:16');
INSERT INTO `activities` VALUES (51, 1, 12, 'Account', 'deleted', 'asdasdddd', 0, '2010-09-17 03:24:39', '2010-09-17 03:24:39');
INSERT INTO `activities` VALUES (52, 1, 9, 'Account', 'deleted', 'asdasd', 0, '2010-09-17 03:24:43', '2010-09-17 03:24:43');
INSERT INTO `activities` VALUES (53, 1, 4, 'Account', 'deleted', 'dfgd', 0, '2010-09-17 03:24:54', '2010-09-17 03:24:54');
INSERT INTO `activities` VALUES (54, 1, 6, 'Account', 'deleted', 'dgdf', 0, '2010-09-17 03:24:57', '2010-09-17 03:24:57');
INSERT INTO `activities` VALUES (55, 1, 5, 'Account', 'deleted', 'dsfsd', 0, '2010-09-17 03:24:58', '2010-09-17 03:24:58');
INSERT INTO `activities` VALUES (56, 1, 16, 'Account', 'deleted', 'dsfsdsdfsd', 0, '2010-09-17 03:25:00', '2010-09-17 03:25:00');
INSERT INTO `activities` VALUES (57, 1, 11, 'Account', 'deleted', 'fdsfsd', 0, '2010-09-17 03:25:01', '2010-09-17 03:25:01');
INSERT INTO `activities` VALUES (58, 1, 1, 'Account', 'deleted', 'mahesh', 0, '2010-09-17 03:25:04', '2010-09-17 03:25:04');
INSERT INTO `activities` VALUES (59, 1, 8, 'Account', 'deleted', 'sdfds', 0, '2010-09-17 03:25:06', '2010-09-17 03:25:06');
INSERT INTO `activities` VALUES (60, 1, 3, 'Account', 'deleted', 'vn', 0, '2010-09-17 03:25:08', '2010-09-17 03:25:08');
INSERT INTO `activities` VALUES (61, 1, 10, 'Account', 'deleted', 'werwe', 0, '2010-09-17 03:25:10', '2010-09-17 03:25:10');
INSERT INTO `activities` VALUES (62, 1, 15, 'Account', 'deleted', 'ytrytr', 0, '2010-09-17 03:25:11', '2010-09-17 03:25:11');
INSERT INTO `activities` VALUES (63, 1, 13, 'Account', 'deleted', 'dsfdsf', 0, '2010-09-17 03:25:21', '2010-09-17 03:25:21');
INSERT INTO `activities` VALUES (64, 1, 2, 'Account', 'deleted', 'gdfg', 0, '2010-09-17 03:25:27', '2010-09-17 03:25:27');
INSERT INTO `activities` VALUES (65, 1, 7, 'Account', 'deleted', 'maheshxcvxv', 0, '2010-09-17 03:25:28', '2010-09-17 03:25:28');
INSERT INTO `activities` VALUES (66, 1, 14, 'Account', 'deleted', 'vxcv', 0, '2010-09-17 03:25:30', '2010-09-17 03:25:30');
INSERT INTO `activities` VALUES (67, 1, 17, 'Account', 'created', 'rtutr', 0, '2010-09-17 03:27:56', '2010-09-17 03:27:56');
INSERT INTO `activities` VALUES (69, 1, 18, 'Account', 'created', 'aaaa', 0, '2010-09-17 03:32:32', '2010-09-17 03:32:32');
INSERT INTO `activities` VALUES (71, 1, 19, 'Account', 'created', 'team selected ', 0, '2010-09-17 03:52:24', '2010-09-17 03:52:24');
INSERT INTO `activities` VALUES (73, 1, 19, 'Account', 'updated', 'team selected chnage to user', 0, '2010-09-17 03:53:06', '2010-09-17 03:53:06');
INSERT INTO `activities` VALUES (74, 1, 19, 'Account', 'updated', 'team selected chnage to user', 0, '2010-09-17 03:54:00', '2010-09-17 03:54:00');
INSERT INTO `activities` VALUES (75, 1, 19, 'Account', 'updated', 'team selected chnage to user remove both', 0, '2010-09-17 03:55:02', '2010-09-17 03:55:02');
INSERT INTO `activities` VALUES (76, 1, 20, 'Account', 'created', 'nagesh', 0, '2010-09-17 04:24:08', '2010-09-17 04:24:08');
INSERT INTO `activities` VALUES (78, 1, 21, 'Account', 'created', 'mahesh', 0, '2010-09-17 04:24:37', '2010-09-17 04:24:37');
INSERT INTO `activities` VALUES (80, 1, 21, 'Account', 'updated', 'mahesh', 0, '2010-09-17 04:25:17', '2010-09-17 04:25:17');
INSERT INTO `activities` VALUES (81, 1, 20, 'Account', 'updated', 'nagesh', 0, '2010-09-17 04:26:23', '2010-09-17 04:26:23');
INSERT INTO `activities` VALUES (82, 1, 22, 'Account', 'created', 'aaa', 0, '2010-09-17 05:49:08', '2010-09-17 05:49:08');
INSERT INTO `activities` VALUES (84, 1, 23, 'Account', 'created', 'sss', 0, '2010-09-17 05:50:09', '2010-09-17 05:50:09');
INSERT INTO `activities` VALUES (86, 1, 19, 'Account', 'deleted', 'team selected chnage to user remove both', 0, '2010-09-17 07:09:34', '2010-09-17 07:09:34');
INSERT INTO `activities` VALUES (87, 1, 23, 'Account', 'deleted', 'sss', 0, '2010-09-17 07:09:38', '2010-09-17 07:09:38');
INSERT INTO `activities` VALUES (88, 1, 22, 'Account', 'deleted', 'aaa', 0, '2010-09-17 07:09:42', '2010-09-17 07:09:42');
INSERT INTO `activities` VALUES (89, 1, 18, 'Account', 'deleted', 'aaaa', 0, '2010-09-17 07:09:44', '2010-09-17 07:09:44');
INSERT INTO `activities` VALUES (90, 1, 21, 'Account', 'deleted', 'mahesh', 0, '2010-09-17 07:09:45', '2010-09-17 07:09:45');
INSERT INTO `activities` VALUES (91, 1, 17, 'Account', 'deleted', 'rtutr', 0, '2010-09-17 07:09:47', '2010-09-17 07:09:47');
INSERT INTO `activities` VALUES (92, 1, 20, 'Account', 'deleted', 'nagesh', 0, '2010-09-17 07:09:51', '2010-09-17 07:09:51');
INSERT INTO `activities` VALUES (93, 1, 1, 'Contact', 'deleted', 'asda asdasd', 0, '2010-09-17 07:09:59', '2010-09-17 07:09:59');
INSERT INTO `activities` VALUES (94, 1, 24, 'Account', 'created', 'Vendor 1', 0, '2010-09-17 07:10:43', '2010-09-17 07:10:43');
INSERT INTO `activities` VALUES (95, 1, 24, 'Account', 'viewed', 'Vendor 1', 0, '2010-09-17 07:10:43', '2010-09-17 08:38:14');
INSERT INTO `activities` VALUES (96, 1, 24, 'Account', 'updated', 'Vendor 1', 0, '2010-09-17 07:13:36', '2010-09-17 07:13:36');
INSERT INTO `activities` VALUES (97, 1, 24, 'Account', 'updated', 'Vendor 1', 0, '2010-09-17 08:37:16', '2010-09-17 08:37:16');
INSERT INTO `activities` VALUES (98, 1, 24, 'Account', 'updated', 'Vendor 1', 0, '2010-09-17 08:37:40', '2010-09-17 08:37:40');
INSERT INTO `activities` VALUES (99, 1, 24, 'Account', 'updated', 'Vendor 1', 0, '2010-09-17 08:38:01', '2010-09-17 08:38:01');
INSERT INTO `activities` VALUES (100, 1, 24, 'Account', 'updated', 'Vendor 1', 0, '2010-09-17 08:38:14', '2010-09-17 08:38:14');

-- --------------------------------------------------------

-- 
-- Table structure for table `addresses`
-- 

CREATE TABLE `addresses` (
  `id` int(11) NOT NULL auto_increment,
  `street1` varchar(255) collate utf8_unicode_ci default NULL,
  `street2` varchar(255) collate utf8_unicode_ci default NULL,
  `city` varchar(64) collate utf8_unicode_ci default NULL,
  `state` varchar(64) collate utf8_unicode_ci default NULL,
  `zipcode` varchar(16) collate utf8_unicode_ci default NULL,
  `country` varchar(64) collate utf8_unicode_ci default NULL,
  `full_address` varchar(255) collate utf8_unicode_ci default NULL,
  `address_type` varchar(16) collate utf8_unicode_ci default NULL,
  `addressable_id` int(11) default NULL,
  `addressable_type` varchar(255) collate utf8_unicode_ci default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `deleted_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_addresses_on_addressable_id_and_addressable_type` (`addressable_id`,`addressable_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=50 ;

-- 
-- Dumping data for table `addresses`
-- 

INSERT INTO `addresses` VALUES (1, NULL, NULL, NULL, NULL, NULL, NULL, 'df', 'Billing', 1, 'Account', '2010-09-15 10:09:20', '2010-09-15 10:09:20', '2010-09-17 03:25:04');
INSERT INTO `addresses` VALUES (2, NULL, NULL, NULL, NULL, NULL, NULL, 'fsf', 'Shipping', 1, 'Account', '2010-09-15 10:09:20', '2010-09-15 10:09:20', '2010-09-17 03:25:04');
INSERT INTO `addresses` VALUES (3, NULL, NULL, NULL, NULL, NULL, NULL, 'dfg', 'Billing', 2, 'Account', '2010-09-15 10:10:44', '2010-09-15 10:10:44', '2010-09-17 03:25:27');
INSERT INTO `addresses` VALUES (4, NULL, NULL, NULL, NULL, NULL, NULL, 'dfg', 'Shipping', 2, 'Account', '2010-09-15 10:10:44', '2010-09-15 10:10:44', '2010-09-17 03:25:27');
INSERT INTO `addresses` VALUES (5, NULL, NULL, NULL, NULL, NULL, NULL, 'fh', 'Billing', 3, 'Account', '2010-09-15 10:29:02', '2010-09-15 10:29:02', '2010-09-17 03:25:08');
INSERT INTO `addresses` VALUES (6, NULL, NULL, NULL, NULL, NULL, NULL, 'fghf', 'Shipping', 3, 'Account', '2010-09-15 10:29:02', '2010-09-15 10:29:02', '2010-09-17 03:25:08');
INSERT INTO `addresses` VALUES (7, NULL, NULL, NULL, NULL, NULL, NULL, 'df', 'Billing', 4, 'Account', '2010-09-15 10:32:17', '2010-09-15 10:32:17', '2010-09-17 03:24:54');
INSERT INTO `addresses` VALUES (8, NULL, NULL, NULL, NULL, NULL, NULL, 'gd', 'Shipping', 4, 'Account', '2010-09-15 10:32:17', '2010-09-15 10:32:17', '2010-09-17 03:24:54');
INSERT INTO `addresses` VALUES (9, NULL, NULL, NULL, NULL, NULL, NULL, 'dsf', 'Billing', 5, 'Account', '2010-09-15 10:33:27', '2010-09-15 10:33:27', '2010-09-17 03:24:58');
INSERT INTO `addresses` VALUES (10, NULL, NULL, NULL, NULL, NULL, NULL, 'sdfs', 'Shipping', 5, 'Account', '2010-09-15 10:33:27', '2010-09-15 10:33:27', '2010-09-17 03:24:58');
INSERT INTO `addresses` VALUES (11, NULL, NULL, NULL, NULL, NULL, NULL, 'dfg', 'Billing', 6, 'Account', '2010-09-15 10:34:53', '2010-09-15 10:34:53', '2010-09-17 03:24:56');
INSERT INTO `addresses` VALUES (12, NULL, NULL, NULL, NULL, NULL, NULL, 'dfgd', 'Shipping', 6, 'Account', '2010-09-15 10:34:53', '2010-09-15 10:34:53', '2010-09-17 03:24:56');
INSERT INTO `addresses` VALUES (13, NULL, NULL, NULL, NULL, NULL, NULL, 'xcvxv', 'Billing', 7, 'Account', '2010-09-15 10:35:35', '2010-09-15 10:35:35', '2010-09-17 03:25:28');
INSERT INTO `addresses` VALUES (14, NULL, NULL, NULL, NULL, NULL, NULL, 'xcv', 'Shipping', 7, 'Account', '2010-09-15 10:35:35', '2010-09-15 10:35:35', '2010-09-17 03:25:28');
INSERT INTO `addresses` VALUES (15, NULL, NULL, NULL, NULL, NULL, NULL, 'tyuyt', 'Business', 1, 'Contact', '2010-09-15 11:27:04', '2010-09-15 11:27:04', '2010-09-17 07:09:58');
INSERT INTO `addresses` VALUES (16, NULL, NULL, NULL, NULL, NULL, NULL, 'dsf', 'Billing', 8, 'Account', '2010-09-15 13:02:24', '2010-09-15 13:02:24', '2010-09-17 03:25:05');
INSERT INTO `addresses` VALUES (17, NULL, NULL, NULL, NULL, NULL, NULL, 'dsfds', 'Shipping', 8, 'Account', '2010-09-15 13:02:24', '2010-09-15 13:02:24', '2010-09-17 03:25:05');
INSERT INTO `addresses` VALUES (18, NULL, NULL, NULL, NULL, NULL, NULL, 'asd', 'Billing', 9, 'Account', '2010-09-16 11:03:32', '2010-09-16 11:03:32', '2010-09-17 03:24:43');
INSERT INTO `addresses` VALUES (19, NULL, NULL, NULL, NULL, NULL, NULL, 'as', 'Shipping', 9, 'Account', '2010-09-16 11:03:32', '2010-09-16 11:03:32', '2010-09-17 03:24:43');
INSERT INTO `addresses` VALUES (20, NULL, NULL, NULL, NULL, NULL, NULL, 'rwe', 'Billing', 10, 'Account', '2010-09-16 11:06:57', '2010-09-16 11:06:57', '2010-09-17 03:25:10');
INSERT INTO `addresses` VALUES (21, NULL, NULL, NULL, NULL, NULL, NULL, 'rwe', 'Shipping', 10, 'Account', '2010-09-16 11:06:57', '2010-09-16 11:06:57', '2010-09-17 03:25:10');
INSERT INTO `addresses` VALUES (22, NULL, NULL, NULL, NULL, NULL, NULL, 'dsfds', 'Billing', 11, 'Account', '2010-09-16 11:47:40', '2010-09-16 11:47:40', '2010-09-17 03:25:01');
INSERT INTO `addresses` VALUES (23, NULL, NULL, NULL, NULL, NULL, NULL, 'fds', 'Shipping', 11, 'Account', '2010-09-16 11:47:40', '2010-09-16 11:47:40', '2010-09-17 03:25:01');
INSERT INTO `addresses` VALUES (24, NULL, NULL, NULL, NULL, NULL, NULL, 'fgh', 'Billing', 12, 'Account', '2010-09-16 11:55:49', '2010-09-16 11:55:49', '2010-09-17 03:24:39');
INSERT INTO `addresses` VALUES (25, NULL, NULL, NULL, NULL, NULL, NULL, 'gfhgfhgf', 'Shipping', 12, 'Account', '2010-09-16 11:55:49', '2010-09-16 11:55:49', '2010-09-17 03:24:39');
INSERT INTO `addresses` VALUES (26, NULL, NULL, NULL, NULL, NULL, NULL, 'dsf', 'Billing', 13, 'Account', '2010-09-16 12:30:53', '2010-09-16 12:30:53', '2010-09-17 03:25:21');
INSERT INTO `addresses` VALUES (27, NULL, NULL, NULL, NULL, NULL, NULL, 'dsf', 'Shipping', 13, 'Account', '2010-09-16 12:30:53', '2010-09-16 12:30:53', '2010-09-17 03:25:21');
INSERT INTO `addresses` VALUES (28, NULL, NULL, NULL, NULL, NULL, NULL, 'xcv', 'Billing', 14, 'Account', '2010-09-16 12:35:58', '2010-09-16 12:35:58', '2010-09-17 03:25:30');
INSERT INTO `addresses` VALUES (29, NULL, NULL, NULL, NULL, NULL, NULL, 'xcvxc', 'Shipping', 14, 'Account', '2010-09-16 12:35:58', '2010-09-16 12:35:58', '2010-09-17 03:25:30');
INSERT INTO `addresses` VALUES (30, NULL, NULL, NULL, NULL, NULL, NULL, 'ytr', 'Billing', 15, 'Account', '2010-09-16 13:14:12', '2010-09-16 13:14:12', '2010-09-17 03:25:11');
INSERT INTO `addresses` VALUES (31, NULL, NULL, NULL, NULL, NULL, NULL, 'ytr', 'Shipping', 15, 'Account', '2010-09-16 13:14:12', '2010-09-16 13:14:12', '2010-09-17 03:25:11');
INSERT INTO `addresses` VALUES (32, NULL, NULL, NULL, NULL, NULL, NULL, 'fds', 'Billing', 16, 'Account', '2010-09-16 13:36:02', '2010-09-16 13:36:02', '2010-09-17 03:25:00');
INSERT INTO `addresses` VALUES (33, NULL, NULL, NULL, NULL, NULL, NULL, 'fds', 'Shipping', 16, 'Account', '2010-09-16 13:36:02', '2010-09-16 13:36:02', '2010-09-17 03:25:00');
INSERT INTO `addresses` VALUES (34, NULL, NULL, NULL, NULL, NULL, NULL, 'utru', 'Billing', 17, 'Account', '2010-09-17 03:27:56', '2010-09-17 03:27:56', '2010-09-17 07:09:47');
INSERT INTO `addresses` VALUES (35, NULL, NULL, NULL, NULL, NULL, NULL, 'trur', 'Shipping', 17, 'Account', '2010-09-17 03:27:56', '2010-09-17 03:27:56', '2010-09-17 07:09:47');
INSERT INTO `addresses` VALUES (36, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Billing', 18, 'Account', '2010-09-17 03:32:32', '2010-09-17 03:32:32', '2010-09-17 07:09:44');
INSERT INTO `addresses` VALUES (37, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Shipping', 18, 'Account', '2010-09-17 03:32:32', '2010-09-17 03:32:32', '2010-09-17 07:09:44');
INSERT INTO `addresses` VALUES (38, NULL, NULL, NULL, NULL, NULL, NULL, 'asdas', 'Billing', 19, 'Account', '2010-09-17 03:52:24', '2010-09-17 03:52:24', '2010-09-17 07:09:34');
INSERT INTO `addresses` VALUES (39, NULL, NULL, NULL, NULL, NULL, NULL, 'dasd', 'Shipping', 19, 'Account', '2010-09-17 03:52:24', '2010-09-17 03:52:24', '2010-09-17 07:09:34');
INSERT INTO `addresses` VALUES (40, NULL, NULL, NULL, NULL, NULL, NULL, 'as', 'Billing', 20, 'Account', '2010-09-17 04:24:08', '2010-09-17 04:24:08', '2010-09-17 07:09:50');
INSERT INTO `addresses` VALUES (41, NULL, NULL, NULL, NULL, NULL, NULL, 'dasd', 'Shipping', 20, 'Account', '2010-09-17 04:24:08', '2010-09-17 04:24:08', '2010-09-17 07:09:50');
INSERT INTO `addresses` VALUES (42, NULL, NULL, NULL, NULL, NULL, NULL, 'as', 'Billing', 21, 'Account', '2010-09-17 04:24:38', '2010-09-17 04:24:38', '2010-09-17 07:09:45');
INSERT INTO `addresses` VALUES (43, NULL, NULL, NULL, NULL, NULL, NULL, 'das', 'Shipping', 21, 'Account', '2010-09-17 04:24:38', '2010-09-17 04:24:38', '2010-09-17 07:09:45');
INSERT INTO `addresses` VALUES (44, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Billing', 22, 'Account', '2010-09-17 05:49:09', '2010-09-17 05:49:09', '2010-09-17 07:09:42');
INSERT INTO `addresses` VALUES (45, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Shipping', 22, 'Account', '2010-09-17 05:49:09', '2010-09-17 05:49:09', '2010-09-17 07:09:42');
INSERT INTO `addresses` VALUES (46, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Billing', 23, 'Account', '2010-09-17 05:50:09', '2010-09-17 05:50:09', '2010-09-17 07:09:38');
INSERT INTO `addresses` VALUES (47, NULL, NULL, NULL, NULL, NULL, NULL, '', 'Shipping', 23, 'Account', '2010-09-17 05:50:09', '2010-09-17 05:50:09', '2010-09-17 07:09:38');
INSERT INTO `addresses` VALUES (48, NULL, NULL, NULL, NULL, NULL, NULL, 'Vendor 1', 'Billing', 24, 'Account', '2010-09-17 07:10:43', '2010-09-17 07:10:43', NULL);
INSERT INTO `addresses` VALUES (49, NULL, NULL, NULL, NULL, NULL, NULL, 'Vendor 1', 'Shipping', 24, 'Account', '2010-09-17 07:10:43', '2010-09-17 07:10:43', NULL);

-- --------------------------------------------------------

-- 
-- Table structure for table `avatars`
-- 

CREATE TABLE `avatars` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `entity_id` int(11) default NULL,
  `entity_type` varchar(255) collate utf8_unicode_ci default NULL,
  `image_file_size` int(11) default NULL,
  `image_file_name` varchar(255) collate utf8_unicode_ci default NULL,
  `image_content_type` varchar(255) collate utf8_unicode_ci default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=3 ;

-- 
-- Dumping data for table `avatars`
-- 

INSERT INTO `avatars` VALUES (2, NULL, 1, 'User', 26025, '6Dv8p.jpg', 'image/jpeg', '2010-09-14 12:06:27', '2010-09-14 12:06:27');

-- --------------------------------------------------------

-- 
-- Table structure for table `campaigns`
-- 

CREATE TABLE `campaigns` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `access` varchar(8) collate utf8_unicode_ci default 'Private',
  `status` varchar(64) collate utf8_unicode_ci default NULL,
  `budget` decimal(12,2) default NULL,
  `target_leads` int(11) default NULL,
  `target_conversion` float default NULL,
  `target_revenue` decimal(12,2) default NULL,
  `leads_count` int(11) default NULL,
  `opportunities_count` int(11) default NULL,
  `revenue` decimal(12,2) default NULL,
  `starts_on` date default NULL,
  `ends_on` date default NULL,
  `objectives` text collate utf8_unicode_ci,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_campaigns_on_user_id_and_name_and_deleted_at` (`user_id`,`name`,`deleted_at`),
  KEY `index_campaigns_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `campaigns`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `comments`
-- 

CREATE TABLE `comments` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `commentable_id` int(11) default NULL,
  `commentable_type` varchar(255) collate utf8_unicode_ci default NULL,
  `private` tinyint(1) default NULL,
  `title` varchar(255) collate utf8_unicode_ci default '',
  `comment` text collate utf8_unicode_ci,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `state` varchar(16) collate utf8_unicode_ci NOT NULL default 'Expanded',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `comments`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `contact_opportunities`
-- 

CREATE TABLE `contact_opportunities` (
  `id` int(11) NOT NULL auto_increment,
  `contact_id` int(11) default NULL,
  `opportunity_id` int(11) default NULL,
  `role` varchar(32) collate utf8_unicode_ci default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `contact_opportunities`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `contacts`
-- 

CREATE TABLE `contacts` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `lead_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `reports_to` int(11) default NULL,
  `first_name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `last_name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `access` varchar(8) collate utf8_unicode_ci default 'Private',
  `title` varchar(64) collate utf8_unicode_ci default NULL,
  `department` varchar(64) collate utf8_unicode_ci default NULL,
  `source` varchar(32) collate utf8_unicode_ci default NULL,
  `email` varchar(64) collate utf8_unicode_ci default NULL,
  `alt_email` varchar(64) collate utf8_unicode_ci default NULL,
  `phone` varchar(32) collate utf8_unicode_ci default NULL,
  `mobile` varchar(32) collate utf8_unicode_ci default NULL,
  `fax` varchar(32) collate utf8_unicode_ci default NULL,
  `blog` varchar(128) collate utf8_unicode_ci default NULL,
  `linkedin` varchar(128) collate utf8_unicode_ci default NULL,
  `facebook` varchar(128) collate utf8_unicode_ci default NULL,
  `twitter` varchar(128) collate utf8_unicode_ci default NULL,
  `born_on` date default NULL,
  `do_not_call` tinyint(1) NOT NULL default '0',
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_contacts_on_user_id_and_last_name_and_deleted_at` (`user_id`,`last_name`,`deleted_at`),
  KEY `index_contacts_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

-- 
-- Dumping data for table `contacts`
-- 

INSERT INTO `contacts` VALUES (1, 1, NULL, NULL, NULL, 'asda', 'asdasd', 'Private', 'tuty', 'uytu', NULL, 'asdasd@sds.kil', 'tyuty', 'ytut', 'uytu', 'uytut', 'tyuyt', 'tyut', 'yut', 'utyu', NULL, 1, '2010-09-17 07:09:59', '2010-09-15 11:27:04', '2010-09-15 11:27:04', NULL);

-- --------------------------------------------------------

-- 
-- Table structure for table `emails`
-- 

CREATE TABLE `emails` (
  `id` int(11) NOT NULL auto_increment,
  `imap_message_id` varchar(255) collate utf8_unicode_ci NOT NULL,
  `user_id` int(11) default NULL,
  `mediator_id` int(11) default NULL,
  `mediator_type` varchar(255) collate utf8_unicode_ci default NULL,
  `sent_from` varchar(255) collate utf8_unicode_ci NOT NULL,
  `sent_to` varchar(255) collate utf8_unicode_ci NOT NULL,
  `cc` varchar(255) collate utf8_unicode_ci default NULL,
  `bcc` varchar(255) collate utf8_unicode_ci default NULL,
  `subject` varchar(255) collate utf8_unicode_ci default NULL,
  `body` text collate utf8_unicode_ci,
  `header` text collate utf8_unicode_ci,
  `sent_at` datetime default NULL,
  `received_at` datetime default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `state` varchar(16) collate utf8_unicode_ci NOT NULL default 'Expanded',
  PRIMARY KEY  (`id`),
  KEY `index_emails_on_mediator_id_and_mediator_type` (`mediator_id`,`mediator_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `emails`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `leads`
-- 

CREATE TABLE `leads` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `campaign_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `first_name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `last_name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `access` varchar(8) collate utf8_unicode_ci default 'Private',
  `title` varchar(64) collate utf8_unicode_ci default NULL,
  `company` varchar(64) collate utf8_unicode_ci default NULL,
  `source` varchar(32) collate utf8_unicode_ci default NULL,
  `status` varchar(32) collate utf8_unicode_ci default NULL,
  `referred_by` varchar(64) collate utf8_unicode_ci default NULL,
  `email` varchar(64) collate utf8_unicode_ci default NULL,
  `alt_email` varchar(64) collate utf8_unicode_ci default NULL,
  `phone` varchar(32) collate utf8_unicode_ci default NULL,
  `mobile` varchar(32) collate utf8_unicode_ci default NULL,
  `blog` varchar(128) collate utf8_unicode_ci default NULL,
  `linkedin` varchar(128) collate utf8_unicode_ci default NULL,
  `facebook` varchar(128) collate utf8_unicode_ci default NULL,
  `twitter` varchar(128) collate utf8_unicode_ci default NULL,
  `rating` int(11) NOT NULL default '0',
  `do_not_call` tinyint(1) NOT NULL default '0',
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_leads_on_user_id_and_last_name_and_deleted_at` (`user_id`,`last_name`,`deleted_at`),
  KEY `index_leads_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `leads`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `main_accounts`
-- 

CREATE TABLE `main_accounts` (
  `id` int(11) NOT NULL auto_increment,
  `subdomain` varchar(255) collate utf8_unicode_ci default NULL,
  `owner_id` int(11) default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=3 ;

-- 
-- Dumping data for table `main_accounts`
-- 

INSERT INTO `main_accounts` VALUES (1, 'mahesh', 1, '2010-09-22 15:10:38', '2010-09-22 15:10:43');
INSERT INTO `main_accounts` VALUES (2, 'nagesh', 2, '2010-09-22 15:10:50', '2010-09-22 15:10:52');

-- --------------------------------------------------------

-- 
-- Table structure for table `opportunities`
-- 

CREATE TABLE `opportunities` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `campaign_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `name` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `access` varchar(8) collate utf8_unicode_ci default 'Private',
  `source` varchar(32) collate utf8_unicode_ci default NULL,
  `stage` varchar(32) collate utf8_unicode_ci default NULL,
  `probability` int(11) default NULL,
  `amount` decimal(12,2) default NULL,
  `discount` decimal(12,2) default NULL,
  `closes_on` date default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_opportunities_on_user_id_and_name_and_deleted_at` (`user_id`,`name`,`deleted_at`),
  KEY `index_opportunities_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `opportunities`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `permissions`
-- 

CREATE TABLE `permissions` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `asset_id` int(11) default NULL,
  `asset_type` varchar(255) collate utf8_unicode_ci default NULL,
  `team_id` int(11) default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_permissions_on_user_id` (`user_id`),
  KEY `index_permissions_on_asset_id_and_asset_type` (`asset_id`,`asset_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=17 ;

-- 
-- Dumping data for table `permissions`
-- 

INSERT INTO `permissions` VALUES (1, 0, NULL, 'Account', 1, '2010-09-17 03:32:31', '2010-09-17 03:32:31');
INSERT INTO `permissions` VALUES (2, 0, NULL, 'Account', 2, '2010-09-17 03:32:32', '2010-09-17 03:32:32');
INSERT INTO `permissions` VALUES (3, 0, NULL, 'Account', 1, '2010-09-17 03:52:24', '2010-09-17 03:52:24');
INSERT INTO `permissions` VALUES (4, 0, NULL, 'Account', 2, '2010-09-17 03:52:24', '2010-09-17 03:52:24');
INSERT INTO `permissions` VALUES (5, 2, NULL, 'Account', 0, '2010-09-17 03:53:06', '2010-09-17 03:53:06');
INSERT INTO `permissions` VALUES (6, 0, NULL, 'Account', 1, '2010-09-17 03:54:00', '2010-09-17 03:54:00');
INSERT INTO `permissions` VALUES (7, 2, NULL, 'Account', 0, '2010-09-17 04:24:08', '2010-09-17 04:24:08');
INSERT INTO `permissions` VALUES (8, 0, NULL, 'Account', 1, '2010-09-17 04:24:37', '2010-09-17 04:24:37');
INSERT INTO `permissions` VALUES (9, 2, 21, 'Account', 0, '2010-09-17 04:25:17', '2010-09-17 04:25:17');
INSERT INTO `permissions` VALUES (10, 0, NULL, 'Account', 2, '2010-09-17 04:26:23', '2010-09-17 04:26:23');
INSERT INTO `permissions` VALUES (11, 2, 20, 'Account', 0, '2010-09-17 04:28:42', '2010-09-17 04:28:42');
INSERT INTO `permissions` VALUES (12, 0, 18, 'Account', 1, '2010-09-17 05:54:50', '2010-09-17 05:54:50');
INSERT INTO `permissions` VALUES (13, 0, 18, 'Account', 2, '2010-09-17 05:54:50', '2010-09-17 05:54:50');
INSERT INTO `permissions` VALUES (14, 0, NULL, 'Account', 3, '2010-09-17 07:13:36', '2010-09-17 07:13:36');
INSERT INTO `permissions` VALUES (15, 2, NULL, 'Account', 0, '2010-09-17 08:37:15', '2010-09-17 08:37:15');
INSERT INTO `permissions` VALUES (16, 0, NULL, 'Account', 3, '2010-09-17 08:37:40', '2010-09-17 08:37:40');

-- --------------------------------------------------------

-- 
-- Table structure for table `preferences`
-- 

CREATE TABLE `preferences` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `name` varchar(32) collate utf8_unicode_ci NOT NULL default '',
  `value` text collate utf8_unicode_ci,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_preferences_on_user_id_and_name` (`user_id`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=4 ;

-- 
-- Dumping data for table `preferences`
-- 

INSERT INTO `preferences` VALUES (1, 1, 'accounts_sort_by', 'BAgiFmFjY291bnRzLm5hbWUgQVND\n', '2010-09-14 12:04:51', '2010-09-14 12:04:51');
INSERT INTO `preferences` VALUES (2, 1, 'accounts_per_page', 'BAgiBzUw\n', '2010-09-14 12:04:58', '2010-09-14 12:04:58');
INSERT INTO `preferences` VALUES (3, 1, 'accounts_outline', 'BAgiCWxvbmc=\n', '2010-09-14 12:05:03', '2010-09-14 12:05:12');

-- --------------------------------------------------------

-- 
-- Table structure for table `schema_migrations`
-- 

CREATE TABLE `schema_migrations` (
  `version` varchar(255) collate utf8_unicode_ci NOT NULL,
  UNIQUE KEY `unique_schema_migrations` (`version`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- 
-- Dumping data for table `schema_migrations`
-- 

INSERT INTO `schema_migrations` VALUES ('1');
INSERT INTO `schema_migrations` VALUES ('10');
INSERT INTO `schema_migrations` VALUES ('11');
INSERT INTO `schema_migrations` VALUES ('12');
INSERT INTO `schema_migrations` VALUES ('13');
INSERT INTO `schema_migrations` VALUES ('14');
INSERT INTO `schema_migrations` VALUES ('15');
INSERT INTO `schema_migrations` VALUES ('16');
INSERT INTO `schema_migrations` VALUES ('17');
INSERT INTO `schema_migrations` VALUES ('18');
INSERT INTO `schema_migrations` VALUES ('19');
INSERT INTO `schema_migrations` VALUES ('2');
INSERT INTO `schema_migrations` VALUES ('20');
INSERT INTO `schema_migrations` VALUES ('21');
INSERT INTO `schema_migrations` VALUES ('22');
INSERT INTO `schema_migrations` VALUES ('23');
INSERT INTO `schema_migrations` VALUES ('24');
INSERT INTO `schema_migrations` VALUES ('25');
INSERT INTO `schema_migrations` VALUES ('26');
INSERT INTO `schema_migrations` VALUES ('27');
INSERT INTO `schema_migrations` VALUES ('28');
INSERT INTO `schema_migrations` VALUES ('29');
INSERT INTO `schema_migrations` VALUES ('3');
INSERT INTO `schema_migrations` VALUES ('30');
INSERT INTO `schema_migrations` VALUES ('31');
INSERT INTO `schema_migrations` VALUES ('32');
INSERT INTO `schema_migrations` VALUES ('33');
INSERT INTO `schema_migrations` VALUES ('34');
INSERT INTO `schema_migrations` VALUES ('35');
INSERT INTO `schema_migrations` VALUES ('36');
INSERT INTO `schema_migrations` VALUES ('4');
INSERT INTO `schema_migrations` VALUES ('5');
INSERT INTO `schema_migrations` VALUES ('6');
INSERT INTO `schema_migrations` VALUES ('7');
INSERT INTO `schema_migrations` VALUES ('8');
INSERT INTO `schema_migrations` VALUES ('9');

-- --------------------------------------------------------

-- 
-- Table structure for table `sessions`
-- 

CREATE TABLE `sessions` (
  `id` int(11) NOT NULL auto_increment,
  `session_id` varchar(1000) collate utf8_unicode_ci NOT NULL,
  `data` text collate utf8_unicode_ci,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_sessions_on_session_id` (`session_id`(255)),
  KEY `index_sessions_on_updated_at` (`updated_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=68 ;

-- 
-- Dumping data for table `sessions`
-- 

INSERT INTO `sessions` VALUES (1, '8e98aea5eed049f31e755f27f391addd', 'BAh7CSIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6FHRp\nbWV6b25lX29mZnNldGkCWE0iCmZsYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6\nOkZsYXNoOjpGbGFzaEhhc2h7AAY6CkB1c2VkewA=\n', '2010-09-13 15:45:44', '2010-09-13 15:46:01');
INSERT INTO `sessions` VALUES (2, '68fc5d2f7ea8df4e418074bff118e3a6', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:47:04', '2010-09-13 15:47:04');
INSERT INTO `sessions` VALUES (3, '82686c8980e95db83dbb8fa2ec456879', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:50:11', '2010-09-13 15:50:11');
INSERT INTO `sessions` VALUES (4, '8c1904f0b4289c3477298472c1e8b15c', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:54:43', '2010-09-13 15:54:43');
INSERT INTO `sessions` VALUES (5, '5a912f511c138cb993377f9dba5706ec', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:56:21', '2010-09-13 15:56:21');
INSERT INTO `sessions` VALUES (6, 'ffc3511c61c713aaf33752554a823a63', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:56:49', '2010-09-13 15:56:49');
INSERT INTO `sessions` VALUES (7, '802e56b7a2572826ab03d01660a4a5d6', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:57:19', '2010-09-13 15:57:19');
INSERT INTO `sessions` VALUES (8, '3106922e6db1cf4fa3cf63ddd03b967a', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-13 15:58:28', '2010-09-13 15:58:28');
INSERT INTO `sessions` VALUES (9, '593695a17591fa44ef01cc95b11e26cb', 'BAh7CyIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6FHRp\nbWV6b25lX29mZnNldGkCWE06GmFjY291bnRzX2N1cnJlbnRfcGFnZWkGOhth\nY2NvdW50c19jdXJyZW50X3F1ZXJ5IgAiCmZsYXNoSUM6J0FjdGlvbkNvbnRy\nb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7AAY6CkB1c2VkewA=\n', '2010-09-14 03:42:41', '2010-09-14 09:53:31');
INSERT INTO `sessions` VALUES (10, 'be41ced56680ae57549341591f81363f', 'BAh7FCIYdXNlcl9jcmVkZW50aWFsc19pZGkGOhBsZWFkX3N0YXR1c1Q6Emxl\nYWRfcHJlc2VuY2VUOhhjYW1wYWlnbl9vYmplY3RpdmVzVCIVdXNlcl9jcmVk\nZW50aWFscyIBgDhkMjRmYzYwMzU0YTUzMTIwYTA5NzEyNjhjNTE5Mzg1YmZi\nNjhhMzFjNTRhY2Q3ZWU1NGRlMWYwMmMzN2E1ZTM1ZTNkNWQ4YTZmYzI0MGUy\nNWZkMWE5ZjJmNjY3YTE5MmRhMzJjMmZlZWRmN2Q4MjVmZTllNDE5NjViZTUx\nMDVmOhRhY2NvdW50X2NvbnRhY3RUOhVsZWFkX3Blcm1pc3Npb25zVDoZY2Ft\ncGFpZ25fcGVybWlzc2lvbnNUOhhhY2NvdW50X3Blcm1pc3Npb25zVDoYY29u\ndGFjdF9wZXJtaXNzaW9uc1Q6EWxlYWRfY29udGFjdFQ6FHRpbWV6b25lX29m\nZnNldGkCWE06FWNvbnRhY3RfcHJlc2VuY2VUOhJjb250YWN0X2V4dHJhVCIK\nZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsA\nBjoKQHVzZWR7AA==\n', '2010-09-15 02:40:32', '2010-09-15 13:40:06');
INSERT INTO `sessions` VALUES (11, 'a036336e14dd39bdbc4d446f9bf56ba7', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6FHRp\nbWV6b25lX29mZnNldGkCWE06GWNhbXBhaWduX3Blcm1pc3Npb25zVCIKZmxh\nc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsABjoK\nQHVzZWR7AA==\n', '2010-09-16 02:54:34', '2010-09-16 07:26:33');
INSERT INTO `sessions` VALUES (12, '7ed8a94142fbdaf902a9d5c8a1ca0485', 'BAh7DiIYdXNlcl9jcmVkZW50aWFsc19pZGkGOhhhY2NvdW50X3Blcm1pc3Np\nb25zVCIVdXNlcl9jcmVkZW50aWFscyIBgDhkMjRmYzYwMzU0YTUzMTIwYTA5\nNzEyNjhjNTE5Mzg1YmZiNjhhMzFjNTRhY2Q3ZWU1NGRlMWYwMmMzN2E1ZTM1\nZTNkNWQ4YTZmYzI0MGUyNWZkMWE5ZjJmNjY3YTE5MmRhMzJjMmZlZWRmN2Q4\nMjVmZTllNDE5NjViZTUxMDVmOhljYW1wYWlnbl9wZXJtaXNzaW9uc1QiGGFj\nY291bnRfbmV3X2NvbW1lbnRUOhVsZWFkX3Blcm1pc3Npb25zVDoUdGltZXpv\nbmVfb2Zmc2V0aQJYTToUYWNjb3VudF9jb250YWN0VCIKZmxhc2hJQzonQWN0\naW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsABjoKQHVzZWR7AA==\n', '2010-09-16 09:59:17', '2010-09-17 09:00:13');
INSERT INTO `sessions` VALUES (13, 'b90e0373eaca99d0a4af1c8ba4071285', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkIOhhhY2NvdW50X3Blcm1pc3Np\nb25zVCIVdXNlcl9jcmVkZW50aWFscyIBgDk4MTE1MjkzOTZhYjMyZjM0YTUz\nYTYzMGE5MDNiZGU5N2VjZWE1NmRlYWMzMzE0OWZkODQ0MjA3OTRiZjQxNmNk\nZmIyMDkyZDBmOWNlYzdhNTI4NWY5NGM4YWM3NDdiMjZlZWFiOTcyYzA5MDFj\nMzQ5OGFiMTg3ZmJiMjZkMzk4OhR0aW1lem9uZV9vZmZzZXRpAlhNIgpmbGFz\naElDOidBY3Rpb25Db250cm9sbGVyOjpGbGFzaDo6Rmxhc2hIYXNoewAGOgpA\ndXNlZHsA\n', '2010-09-17 07:11:10', '2010-09-17 09:00:31');
INSERT INTO `sessions` VALUES (14, 'd88b3d7a26efc708fb692c3cab8ef5de', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6DnJl\ndHVybl90byIGLyIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6\nOkZsYXNoSGFzaHsGOgtub3RpY2UiQ1dlbGNvbWUgdG8gRmF0IEZyZWUgQ1JN\nISBZb3VyIGxhc3QgbG9naW4gd2FzIG9uIFNlcCAgYXQgOjM1YW0uBjoKQHVz\nZWR7BjsHRjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-22 04:46:32', '2010-09-22 11:38:09');
INSERT INTO `sessions` VALUES (15, '8df60023df2d3e1356b37769b1e0ad88', 'BAh7CDoOcmV0dXJuX3RvIgYvIgpmbGFzaElDOidBY3Rpb25Db250cm9sbGVy\nOjpGbGFzaDo6Rmxhc2hIYXNoewAGOgpAdXNlZHsAOhR0aW1lem9uZV9vZmZz\nZXRpAlhN\n', '2010-09-22 09:20:10', '2010-09-22 11:38:11');
INSERT INTO `sessions` VALUES (16, 'e2691e287d98bc2287d1fc25e6fb179f', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6DnJl\ndHVybl90byIGLyIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6\nOkZsYXNoSGFzaHsABjoKQHVzZWR7ADoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-22 11:38:51', '2010-09-22 11:56:19');
INSERT INTO `sessions` VALUES (17, '17f35ec87444b6bee71d9735d3fd1897', 'BAh7CDoOcmV0dXJuX3RvIgYvIgpmbGFzaElDOidBY3Rpb25Db250cm9sbGVy\nOjpGbGFzaDo6Rmxhc2hIYXNoewAGOgpAdXNlZHsAOhR0aW1lem9uZV9vZmZz\nZXRpAlhN\n', '2010-09-22 11:39:00', '2010-09-22 11:56:03');
INSERT INTO `sessions` VALUES (18, '9421c7587704dff7bffc6a35100bfeba', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-22 11:56:32', '2010-09-22 11:56:33');
INSERT INTO `sessions` VALUES (19, '493c563e36dd602735d16ab1f5a01d34', 'BAh7CDoUdGltZXpvbmVfb2Zmc2V0aQJYTToOcmV0dXJuX3RvIgYvIgpmbGFz\naElDOidBY3Rpb25Db250cm9sbGVyOjpGbGFzaDo6Rmxhc2hIYXNoewAGOgpA\ndXNlZHsA\n', '2010-09-22 12:07:28', '2010-09-22 13:28:19');
INSERT INTO `sessions` VALUES (20, 'df9d4383b7b8379f65cde77ad94ef5e5', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkGOhR0aW1lem9uZV9vZmZzZXRp\nAlhNIhV1c2VyX2NyZWRlbnRpYWxzIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3\nMTI2OGM1MTkzODViZmI2OGEzMWM1NGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVl\nM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlmMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgy\nNWZlOWU0MTk2NWJlNTEwNWY6DnJldHVybl90byIGLyIKZmxhc2hJQzonQWN0\naW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiQ1dl\nbGNvbWUgdG8gRmF0IEZyZWUgQ1JNISBZb3VyIGxhc3QgbG9naW4gd2FzIG9u\nIFNlcCAgYXQgOjIxcG0uBjoKQHVzZWR7BjsIRg==\n', '2010-09-22 12:07:54', '2010-09-22 13:28:02');
INSERT INTO `sessions` VALUES (21, 'edc961c3c666535f200bf2be3777d43b', 'BAh7AA==\n', '2010-09-23 04:02:42', '2010-09-23 04:02:42');
INSERT INTO `sessions` VALUES (22, 'fa8dade8f66fd7926f4f44b6c2ec88c1', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 04:02:44', '2010-09-23 04:02:44');
INSERT INTO `sessions` VALUES (23, '365f8964042adc4e8575444689e28fa6', 'BAh7CCIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWYiCmZs\nYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7BjoL\nbm90aWNlIkNXZWxjb21lIHRvIEZhdCBGcmVlIENSTSEgWW91ciBsYXN0IGxv\nZ2luIHdhcyBvbiBTZXAgIGF0IDo1OGFtLgY6CkB1c2VkewY7BkY=\n', '2010-09-23 04:02:50', '2010-09-23 04:02:50');
INSERT INTO `sessions` VALUES (24, '0f98086082c1defe121b2162ac9d0286', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-23 04:02:52', '2010-09-23 04:02:52');
INSERT INTO `sessions` VALUES (25, 'fb1e0bc07dbed24d32ed2633ac6664a2', 'BAh7AA==\n', '2010-09-23 04:02:54', '2010-09-23 04:02:54');
INSERT INTO `sessions` VALUES (26, '1988a3ab6aae03c47f68a6c27173c17c', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 04:02:55', '2010-09-23 04:02:55');
INSERT INTO `sessions` VALUES (27, 'b602c35f03e419d5f031c234f572ba6d', 'BAh7AA==\n', '2010-09-23 04:04:08', '2010-09-23 04:04:08');
INSERT INTO `sessions` VALUES (28, '0e42717342d6650d5a09372145a4d331', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 04:04:10', '2010-09-23 04:04:10');
INSERT INTO `sessions` VALUES (29, '4fd9ba700478619a571133c48026d5c3', 'BAh7CCIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWYiCmZs\nYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7BjoL\nbm90aWNlIkNXZWxjb21lIHRvIEZhdCBGcmVlIENSTSEgWW91ciBsYXN0IGxv\nZ2luIHdhcyBvbiBTZXAgIGF0IDowMmFtLgY6CkB1c2VkewY7BkY=\n', '2010-09-23 04:04:16', '2010-09-23 04:04:16');
INSERT INTO `sessions` VALUES (30, '99af797d827ab4b0ffaa014133b94bb5', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-23 04:04:18', '2010-09-23 04:04:18');
INSERT INTO `sessions` VALUES (31, '52cbc70160bae2f314c64407b9793bdf', 'BAh7AA==\n', '2010-09-23 04:04:19', '2010-09-23 04:04:19');
INSERT INTO `sessions` VALUES (32, '358868a0b41a3718f0cde71abcd55b31', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 04:04:21', '2010-09-23 04:04:21');
INSERT INTO `sessions` VALUES (33, 'BAh7CToUdGltZXpvbmVfb2Zmc2V0aQJYTToOcmV0dXJuX3RvIgYvOg9zZXNzaW9uX2lkIiUxNWM5MTA5ZjE4NjI2MDBiODk0MTg5YmViN2ZhOWNkNCIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiQFlvdSBoYXZlIGJlZW4gbG9nZ2VkIG91dC4gVGhhbmsgeW91IGZvciB1c2luZyBGYXQgRnJlZSBDUk0hBjoKQHVzZWR7BjsJVA==--3923fb58c0c4dec64f6befe080b7954a6e6fb5f2', 'BAh7CDoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB1Q6FHRpbWV6b25lX29mZnNldGkCWE0=\n', '2010-09-23 05:44:19', '2010-09-23 06:19:07');
INSERT INTO `sessions` VALUES (34, 'BAh7CyIYdXNlcl9jcmVkZW50aWFsc19pZGkGOhR0aW1lem9uZV9vZmZzZXRpAlhNIhV1c2VyX2NyZWRlbnRpYWxzIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1NGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlmMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6DnJldHVybl90byIGLzoPc2Vzc2lvbl9pZCIlNmExMDE3NTU3NjM1NDk0OTAzMjVlYTc3MTRiMzVhYjgiCmZsYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7BjoLbm90aWNlIkNXZWxjb21lIHRvIEZhdCBGcmVlIENSTSEgWW91ciBsYXN0IGxvZ2luIHdhcyBvbiBTZXAgIGF0IDoyOHBtLgY6CkB1c2VkewY7CVQ=--ca2fbed3783fac06d9310c348a536b313aebb1c6', 'BAh7CjoOcmV0dXJuX3RvIgYvIhh1c2VyX2NyZWRlbnRpYWxzX2lkaQYiFXVz\nZXJfY3JlZGVudGlhbHMiAYA4ZDI0ZmM2MDM1NGE1MzEyMGEwOTcxMjY4YzUx\nOTM4NWJmYjY4YTMxYzU0YWNkN2VlNTRkZTFmMDJjMzdhNWUzNWUzZDVkOGE2\nZmMyNDBlMjVmZDFhOWYyZjY2N2ExOTJkYTMyYzJmZWVkZjdkODI1ZmU5ZTQx\nOTY1YmU1MTA1ZiIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6\nOkZsYXNoSGFzaHsGOgtub3RpY2UiQ1dlbGNvbWUgdG8gRmF0IEZyZWUgQ1JN\nISBZb3VyIGxhc3QgbG9naW4gd2FzIG9uIFNlcCAgYXQgOjE3YW0uBjoKQHVz\nZWR7BjsHVDoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 05:47:46', '2010-09-23 06:18:30');
INSERT INTO `sessions` VALUES (35, '05da5e7d4ce557d30537dd2f5795bbbd', 'BAh7AA==\n', '2010-09-23 07:11:20', '2010-09-23 07:11:20');
INSERT INTO `sessions` VALUES (36, 'b9b0091dd14c2d6bda4082ee45fb1ee8', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 07:11:21', '2010-09-23 07:11:21');
INSERT INTO `sessions` VALUES (37, '3dfd8a88b822b9a57b53fdbc46db22be', 'BAh7CCIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWYiCmZs\nYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7BjoL\nbm90aWNlIkNXZWxjb21lIHRvIEZhdCBGcmVlIENSTSEgWW91ciBsYXN0IGxv\nZ2luIHdhcyBvbiBTZXAgIGF0IDowOWFtLgY6CkB1c2VkewY7BkY=\n', '2010-09-23 07:11:27', '2010-09-23 07:11:27');
INSERT INTO `sessions` VALUES (38, '064a0806fa7b21c6d4ff7c704a0e9a88', 'BAh7BzoOcmV0dXJuX3RvIg0vcHJvZmlsZSIKZmxhc2hJQzonQWN0aW9uQ29u\ndHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsGOgtub3RpY2UiL1lvdSBtdXN0\nIGJlIGxvZ2dlZCBpbiB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7\nB0Y=\n', '2010-09-23 07:11:29', '2010-09-23 07:11:29');
INSERT INTO `sessions` VALUES (39, '9b6f9c39b174ad5bf56f75c1c78b0b9b', 'BAh7AA==\n', '2010-09-23 07:11:31', '2010-09-23 07:11:31');
INSERT INTO `sessions` VALUES (40, 'd5997a31f20f0f16449919134662c954', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 07:11:32', '2010-09-23 07:11:32');
INSERT INTO `sessions` VALUES (41, '7c757e5c45f4e28693af6d89b0fbaf59', 'BAh7BjoOcmV0dXJuX3RvIgYv\n', '2010-09-23 07:13:56', '2010-09-23 07:13:56');
INSERT INTO `sessions` VALUES (42, '5d5521a1d543e4312c03ebcc52e7db6c', 'BAh7AA==\n', '2010-09-23 07:13:58', '2010-09-23 07:13:58');
INSERT INTO `sessions` VALUES (43, '552625b2c4f15567160116fccfb75645', 'BAh7CjoOcmV0dXJuX3RvIgsvbG9naW4iGHVzZXJfY3JlZGVudGlhbHNfaWRp\nBiIVdXNlcl9jcmVkZW50aWFscyIBgDhkMjRmYzYwMzU0YTUzMTIwYTA5NzEy\nNjhjNTE5Mzg1YmZiNjhhMzFjNTRhY2Q3ZWU1NGRlMWYwMmMzN2E1ZTM1ZTNk\nNWQ4YTZmYzI0MGUyNWZkMWE5ZjJmNjY3YTE5MmRhMzJjMmZlZWRmN2Q4MjVm\nZTllNDE5NjViZTUxMDVmIgpmbGFzaElDOidBY3Rpb25Db250cm9sbGVyOjpG\nbGFzaDo6Rmxhc2hIYXNoewY6C25vdGljZSIwWW91IG11c3QgYmUgbG9nZ2Vk\nIG91dCB0byBhY2Nlc3MgdGhpcyBwYWdlLgY6CkB1c2VkewY7B1Q6FHRpbWV6\nb25lX29mZnNldGkCWE0=\n', '2010-09-23 07:15:15', '2010-09-23 07:21:22');
INSERT INTO `sessions` VALUES (44, 'BAh7CToOcmV0dXJuX3RvIgwvbG9nb3V0IgpmbGFzaElDOidBY3Rpb25Db250cm9sbGVyOjpGbGFzaDo6Rmxhc2hIYXNoewY6C25vdGljZSIvWW91IG11c3QgYmUgbG9nZ2VkIGluIHRvIGFjY2VzcyB0aGlzIHBhZ2UuBjoKQHVzZWR7BjsHVDoPc2Vzc2lvbl9pZCIlNzY0MzZiZjAwNzAzZTBhMTQ1ZmQwMmFhNDQxNTMzODc6FHRpbWV6b25lX29mZnNldGkCWE0=--a3bdb0fbaf60e0c99193ca9358b34401d15ed186', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkHOg5yZXR1cm5fdG8iBi8iFXVz\nZXJfY3JlZGVudGlhbHMiAYAzZDQ1NDEzZjhjNTJmNWYwMTQ3NjU1YTlkMDU1\nYmFhMDllODYxZjUzOTRkYzZkNDkyMzc3YjY3MTcyNzkyNDAyNTIwMmY2MGQz\nNWJmYjEyODkzYzQ5Yzc2ODE1YmM3ZWRlYzNmZWE0ZTcxMTI2MjRiZmY1NTll\nYjEzYWRmNDMyNSIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6\nOkZsYXNoSGFzaHsABjoKQHVzZWR7ADoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-09-23 10:46:10', '2010-09-23 12:11:47');
INSERT INTO `sessions` VALUES (45, 'b4ff77ad7f32d13a45c856248fdb16e7', 'BAh7BjoOcmV0dXJuX3RvIgYv\n', '2010-09-24 05:53:09', '2010-09-24 05:53:09');
INSERT INTO `sessions` VALUES (46, '1d85fc14bcb6c05129c4f462b6598615', 'BAh7AA==\n', '2010-09-24 05:53:11', '2010-09-24 05:53:11');
INSERT INTO `sessions` VALUES (47, '2cc4f18f0cff815276bafe980f312def', 'BAh7AA==\n', '2010-09-24 05:53:22', '2010-09-24 05:53:22');
INSERT INTO `sessions` VALUES (48, 'f9c1c8ff98ef1344a14a5440d3882544', 'BAh7AA==\n', '2010-09-24 05:53:23', '2010-09-24 05:53:23');
INSERT INTO `sessions` VALUES (49, '26b2267f99b0cdc1518f20ec8cc13947', 'BAh7AA==\n', '2010-09-24 05:53:42', '2010-09-24 05:53:42');
INSERT INTO `sessions` VALUES (50, '1edce6df322c06f392a96a01406131bb', 'BAh7AA==\n', '2010-09-24 05:53:43', '2010-09-24 05:53:43');
INSERT INTO `sessions` VALUES (51, '41d99f6aef77c1c9a0411e47e30827fe', 'BAh7AA==\n', '2010-09-24 05:53:58', '2010-09-24 05:53:58');
INSERT INTO `sessions` VALUES (52, '5a493d6519c3e2a7dfb3e99a84fecf2b', 'BAh7AA==\n', '2010-09-24 05:54:00', '2010-09-24 05:54:00');
INSERT INTO `sessions` VALUES (53, 'a69b646da7c7c0a2c6b9c88a7242e288', 'BAh7AA==\n', '2010-09-24 05:54:16', '2010-09-24 05:54:16');
INSERT INTO `sessions` VALUES (54, 'dad693311b13eb44511e3351342d90f0', 'BAh7AA==\n', '2010-09-24 05:54:17', '2010-09-24 05:54:17');
INSERT INTO `sessions` VALUES (55, '438d02af4d55c7ecb06714a3e5e0e2a2', 'BAh7AA==\n', '2010-09-24 05:56:21', '2010-09-24 05:56:21');
INSERT INTO `sessions` VALUES (56, 'ea23b5abf8b84cd0f9749f8044928d9d', 'BAh7AA==\n', '2010-09-24 05:56:22', '2010-09-24 05:56:22');
INSERT INTO `sessions` VALUES (57, '90acfb8c0186fc1e81d8a056b7231ba2', 'BAh7BjoOcmV0dXJuX3RvIgYv\n', '2010-10-05 08:55:38', '2010-10-05 08:55:38');
INSERT INTO `sessions` VALUES (58, '2e291624b6614ddca5e5f1f255c34586', 'BAh7AA==\n', '2010-10-05 08:55:39', '2010-10-05 08:55:39');
INSERT INTO `sessions` VALUES (59, 'c2a7b1cc2c55ac338594c6a2ae9591b1', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-10-05 08:55:41', '2010-10-05 08:55:41');
INSERT INTO `sessions` VALUES (60, '6211266c2074b62766c9adb08c040669', 'BAh7AA==\n', '2010-10-05 08:55:48', '2010-10-05 08:55:48');
INSERT INTO `sessions` VALUES (61, 'f0ce6ccfde0b44bbdb4547924bc00351', 'BAh7AA==\n', '2010-10-05 08:56:33', '2010-10-05 08:56:33');
INSERT INTO `sessions` VALUES (62, 'bb2fb29e0e18a481fe7eec490bd4f22c', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-10-05 08:56:34', '2010-10-05 08:56:34');
INSERT INTO `sessions` VALUES (63, 'd627b74e2075c62ba5e6ec99afeb9944', 'BAh7BjoOcmV0dXJuX3RvIgYv\n', '2010-11-26 04:28:36', '2010-11-26 04:28:36');
INSERT INTO `sessions` VALUES (64, '9472bdedd4dd2e00228ba34fb9bb7c5f', 'BAh7AA==\n', '2010-11-26 04:28:38', '2010-11-26 04:28:38');
INSERT INTO `sessions` VALUES (65, '38807b875407154049bb4cc163de0b7e', 'BAh7BjoUdGltZXpvbmVfb2Zmc2V0aQJYTQ==\n', '2010-11-26 04:28:39', '2010-11-26 04:28:39');
INSERT INTO `sessions` VALUES (66, '56b2ba57db0056babce892f1275e36cc', 'BAh7CCIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWYiCmZs\nYXNoSUM6J0FjdGlvbkNvbnRyb2xsZXI6OkZsYXNoOjpGbGFzaEhhc2h7BjoL\nbm90aWNlIkNXZWxjb21lIHRvIEZhdCBGcmVlIENSTSEgWW91ciBsYXN0IGxv\nZ2luIHdhcyBvbiBTZXAgIGF0IDo0M2FtLgY6CkB1c2VkewY7BkY=\n', '2010-11-26 04:28:47', '2010-11-26 04:28:47');
INSERT INTO `sessions` VALUES (67, '0198e9a9178e883f9041c3b0ab347270', 'BAh7CiIYdXNlcl9jcmVkZW50aWFsc19pZGkGIhV1c2VyX2NyZWRlbnRpYWxz\nIgGAOGQyNGZjNjAzNTRhNTMxMjBhMDk3MTI2OGM1MTkzODViZmI2OGEzMWM1\nNGFjZDdlZTU0ZGUxZjAyYzM3YTVlMzVlM2Q1ZDhhNmZjMjQwZTI1ZmQxYTlm\nMmY2NjdhMTkyZGEzMmMyZmVlZGY3ZDgyNWZlOWU0MTk2NWJlNTEwNWY6DnJl\ndHVybl90byIGLzoUdGltZXpvbmVfb2Zmc2V0aQJYTSIKZmxhc2hJQzonQWN0\naW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNoSGFzaHsABjoKQHVzZWR7AA==\n', '2010-11-26 04:30:52', '2010-11-26 05:47:23');

-- --------------------------------------------------------

-- 
-- Table structure for table `settings`
-- 

CREATE TABLE `settings` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(32) collate utf8_unicode_ci NOT NULL default '',
  `value` text collate utf8_unicode_ci,
  `default_value` text collate utf8_unicode_ci,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`),
  KEY `index_settings_on_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=23 ;

-- 
-- Dumping data for table `settings`
-- 

INSERT INTO `settings` VALUES (1, 'user_signup', NULL, 'BAg6EG5vdF9hbGxvd2Vk\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (2, 'campaign_status', NULL, 'BAhbCjoMcGxhbm5lZDoMc3RhcnRlZDoOY29tcGxldGVkOgxvbl9ob2xkOg9j\nYWxsZWRfb2Zm\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (3, 'task_category', NULL, 'BAhbDToJY2FsbDoKZW1haWw6DmZvbGxvd191cDoKbHVuY2g6DG1lZXRpbmc6\nCm1vbmV5OhFwcmVzZW50YXRpb246CXRyaXA=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (4, 'task_calendar_with_time', NULL, 'BAhG\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (5, 'lead_status_color', NULL, 'BAh7CToNcmVqZWN0ZWQiDHRoaXN0bGU6DmNvbnZlcnRlZCILYmlzcXVlOg5j\nb250YWN0ZWQiEnBhbGV0dXJxdW9pc2U6CG5ldyIOcGFsZWdyZWVu\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (6, 'default_access', NULL, 'BAgiDFByaXZhdGU=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (7, 'locale', NULL, 'BAgiCmVuLVVT\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (8, 'opportunity_stage_color', NULL, 'BAh7DToNcHJvcG9zYWwiDHRoaXN0bGU6DWFuYWx5c2lzIg5taXN0eXJvc2U6\nCWxvc3QiCXBpbms6CHdvbiIPbGlnaHRncmVlbjoQcHJvc3BlY3RpbmciDWxh\ndmVuZGVyOhFmaW5hbF9yZXZpZXciD2FxdWFtYXJpbmU6EG5lZ290aWF0aW9u\nIgxza3libHVlOhFwcmVzZW50YXRpb24iCndoZWF0\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (9, 'email_dropbox', NULL, 'BAh7DzobbW92ZV9pbnZhbGlkX3RvX2ZvbGRlciIMaW52YWxpZDoMYWRkcmVz\ncyIYZHJvcGJveEBleGFtcGxlLmNvbToLc2VydmVyIhVpbWFwLmV4YW1wbGUu\nY29tOhZhdHRhY2hfdG9fYWNjb3VudEY6CXBvcnRpAuEDOgl1c2VyIhV1c2Vy\nQGV4YW1wbGUuY29tOhBzY2FuX2ZvbGRlciIKaW5ib3g6DXBhc3N3b3JkIg1w\nYXNzd29yZDoTbW92ZV90b19mb2xkZXIiDnByb2Nlc3NlZDoIc3NsVA==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (10, 'admin_tabs', NULL, 'BAhbCHsIOgh1cmx7BjoPY29udHJvbGxlciIQYWRtaW4vdXNlcnM6CXRleHQ6\nFGFkbWluX3RhYl91c2VyczoLYWN0aXZlVHsIOwB7BjsGIhNhZG1pbi9zZXR0\naW5nczsHOhdhZG1pbl90YWJfc2V0dGluZ3M7CUZ7CDsAewY7BiISYWRtaW4v\ncGx1Z2luczsHOhZhZG1pbl90YWJfcGx1Z2luczsJRg==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (11, 'compound_address', NULL, 'BAhG\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (12, 'task_completed', NULL, 'BAhbCjoUY29tcGxldGVkX3RvZGF5Ohhjb21wbGV0ZWRfeWVzdGVyZGF5Ohhj\nb21wbGV0ZWRfbGFzdF93ZWVrOhljb21wbGV0ZWRfdGhpc19tb250aDoZY29t\ncGxldGVkX2xhc3RfbW9udGg=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (13, 'opportunity_stage', NULL, 'BAhbDToQcHJvc3BlY3Rpbmc6DWFuYWx5c2lzOhFwcmVzZW50YXRpb246DXBy\nb3Bvc2FsOhBuZWdvdGlhdGlvbjoRZmluYWxfcmV2aWV3Ogh3b246CWxvc3Q=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (14, 'background_info', NULL, 'BAhbAA==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (15, 'task_bucket', NULL, 'BAhbDDoMb3ZlcmR1ZToNZHVlX2FzYXA6DmR1ZV90b2RheToRZHVlX3RvbW9y\ncm93OhJkdWVfdGhpc193ZWVrOhJkdWVfbmV4dF93ZWVrOg5kdWVfbGF0ZXI=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (16, 'lead_source', NULL, 'BAhbDjoNY2FtcGFpZ246DmNvbGRfY2FsbDoPY29uZmVyZW5jZToLb25saW5l\nOg1yZWZlcnJhbDoJc2VsZjoId2ViOhJ3b3JkX29mX21vdXRoOgpvdGhlcg==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (17, 'tabs', NULL, 'BAhbDHsIOgh1cmx7BjoPY29udHJvbGxlciIGLzoJdGV4dDoSdGFiX2Rhc2hi\nb2FyZDoLYWN0aXZlVHsIOwB7BjsGIgp0YXNrczsHOg50YWJfdGFza3M7CUZ7\nCDsAewY7BiIOY2FtcGFpZ25zOwc6EnRhYl9jYW1wYWlnbnM7CUZ7CDsAewY7\nBiIKbGVhZHM7BzoOdGFiX2xlYWRzOwlGewg7AHsGOwYiDWFjY291bnRzOwc6\nEXRhYl9hY2NvdW50czsJRnsIOwB7BjsGIg1jb250YWN0czsHOhF0YWJfY29u\ndGFjdHM7CUZ7CDsAewY7BiISb3Bwb3J0dW5pdGllczsHOhZ0YWJfb3Bwb3J0\ndW5pdGllczsJRg==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (18, 'base_url', NULL, 'BAgiAA==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (19, 'campaign_status_color', NULL, 'BAh7CjoPY2FsbGVkX29mZiIMdGhpc3RsZToMb25faG9sZCIJcGluazoMc3Rh\ncnRlZCIScGFsZXR1cnF1b2lzZToOY29tcGxldGVkIgtiaXNxdWU6DHBsYW5u\nZWQiDnBhbGVncmVlbg==\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (20, 'task_category_color', NULL, 'BAh7DToKZW1haWwiEnBhbGV0dXJxdW9pc2U6DG1lZXRpbmciDHRoaXN0bGU6\nCWNhbGwiDWxhdmVuZGVyOg5mb2xsb3dfdXAiDm1pc3R5cm9zZToKbHVuY2gi\nCndoZWF0Ogl0cmlwIgxza3libHVlOhFwcmVzZW50YXRpb24iD2FxdWFtYXJp\nbmU6Cm1vbmV5Ig9saWdodGdyZWVu\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (21, 'lead_status', NULL, 'BAhbCToIbmV3Og5jb250YWN0ZWQ6DmNvbnZlcnRlZDoNcmVqZWN0ZWQ=\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');
INSERT INTO `settings` VALUES (22, 'per_user_locale', NULL, 'BAhG\n', '2010-09-13 21:14:44', '2010-09-13 21:14:44');

-- --------------------------------------------------------

-- 
-- Table structure for table `tasks`
-- 

CREATE TABLE `tasks` (
  `id` int(11) NOT NULL auto_increment,
  `user_id` int(11) default NULL,
  `assigned_to` int(11) default NULL,
  `completed_by` int(11) default NULL,
  `name` varchar(255) collate utf8_unicode_ci NOT NULL default '',
  `asset_id` int(11) default NULL,
  `asset_type` varchar(255) collate utf8_unicode_ci default NULL,
  `priority` varchar(32) collate utf8_unicode_ci default NULL,
  `category` varchar(32) collate utf8_unicode_ci default NULL,
  `bucket` varchar(32) collate utf8_unicode_ci default NULL,
  `due_at` datetime default NULL,
  `completed_at` datetime default NULL,
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `background_info` varchar(255) collate utf8_unicode_ci default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_tasks_on_user_id_and_name_and_deleted_at` (`user_id`,`name`,`deleted_at`),
  KEY `index_tasks_on_assigned_to` (`assigned_to`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- 
-- Dumping data for table `tasks`
-- 


-- --------------------------------------------------------

-- 
-- Table structure for table `teams`
-- 

CREATE TABLE `teams` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(36) collate utf8_unicode_ci default NULL,
  `user_id` int(11) NOT NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=4 ;

-- 
-- Dumping data for table `teams`
-- 

INSERT INTO `teams` VALUES (1, 'team a', 1, '2010-09-16 04:06:21', '2010-09-16 04:06:21');
INSERT INTO `teams` VALUES (2, 'team two', 1, '2010-09-16 04:14:58', '2010-09-16 04:14:58');
INSERT INTO `teams` VALUES (3, 'raju team', 1, '2010-09-17 07:09:03', '2010-09-17 07:09:03');

-- --------------------------------------------------------

-- 
-- Table structure for table `users`
-- 

CREATE TABLE `users` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(32) collate utf8_unicode_ci NOT NULL default '',
  `email` varchar(64) collate utf8_unicode_ci NOT NULL default '',
  `first_name` varchar(32) collate utf8_unicode_ci default NULL,
  `last_name` varchar(32) collate utf8_unicode_ci default NULL,
  `title` varchar(64) collate utf8_unicode_ci default NULL,
  `company` varchar(64) collate utf8_unicode_ci default NULL,
  `alt_email` varchar(64) collate utf8_unicode_ci default NULL,
  `phone` varchar(32) collate utf8_unicode_ci default NULL,
  `mobile` varchar(32) collate utf8_unicode_ci default NULL,
  `aim` varchar(32) collate utf8_unicode_ci default NULL,
  `yahoo` varchar(32) collate utf8_unicode_ci default NULL,
  `google` varchar(32) collate utf8_unicode_ci default NULL,
  `skype` varchar(32) collate utf8_unicode_ci default NULL,
  `password_hash` varchar(255) collate utf8_unicode_ci NOT NULL default '',
  `password_salt` varchar(255) collate utf8_unicode_ci NOT NULL default '',
  `persistence_token` varchar(255) collate utf8_unicode_ci NOT NULL default '',
  `perishable_token` varchar(255) collate utf8_unicode_ci NOT NULL default '',
  `last_request_at` datetime default NULL,
  `last_login_at` datetime default NULL,
  `current_login_at` datetime default NULL,
  `last_login_ip` varchar(255) collate utf8_unicode_ci default NULL,
  `current_login_ip` varchar(255) collate utf8_unicode_ci default NULL,
  `login_count` int(11) NOT NULL default '0',
  `deleted_at` datetime default NULL,
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  `admin` tinyint(1) NOT NULL default '0',
  `suspended_at` datetime default NULL,
  `team_id` int(11) default NULL,
  `main_account_id` int(11) default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `index_users_on_username_and_deleted_at` (`username`,`deleted_at`),
  KEY `index_users_on_email` (`email`),
  KEY `index_users_on_last_request_at` (`last_request_at`),
  KEY `index_users_on_remember_token` (`persistence_token`),
  KEY `index_users_on_perishable_token` (`perishable_token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=4 ;

-- 
-- Dumping data for table `users`
-- 

INSERT INTO `users` VALUES (1, 'umamahesh', 'umamahesh_nyros@yahoo.com', '', '', '', '', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '64fd56a0d25d80930e70a1dc68e6ffad1790181fdc8ad3b4faa46c6b2bcd21facc5c225714c827a043c17082b1caa6d8adaab69aacd99f95c702db049c4c503f', '0eV1KwlXbEbRRJwRp4Kz', '8d24fc60354a53120a0971268c519385bfb68a31c54acd7ee54de1f02c37a5e35e3d5d8a6fc240e25fd1a9f2f667a192da32c2feedf7d825fe9e41965be5105f', 'PIR5NtzhZijM4RG00h0M', '2010-11-26 07:17:51', '2010-11-26 04:30:59', '2010-11-26 05:47:15', '127.0.0.1', '127.0.0.1', 116, NULL, '2010-09-13 15:44:59', '2010-11-26 07:17:51', 1, NULL, NULL, 1);
INSERT INTO `users` VALUES (2, 'nagesh', 'nagesh_nyros@yahoo.com', 'nagesh', 'nagesh', 'team coordibator', 'nyros', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'b64b2e228789b0b74d9aa6f9cac2d30b8322d16c72babc12da7eb70e7fc8ed070fc1785231e5062639830b96f77bfea69607ab90e6a1fd6a70c76d7c6f020246', '_7NkK_1hSWnLuEBk933F', '3d45413f8c52f5f0147655a9d055baa09e861f5394dc6d492377b671727924025202f60d35bfb12893c49c76815bc7edec3fea4e7112624bff559eb13adf4325', 'UyU1YnDA8o5F6QUycIH9', '2010-09-23 12:07:49', '2010-09-23 11:43:57', '2010-09-23 12:07:37', '127.0.0.1', '127.0.0.1', 8, NULL, '2010-09-16 04:06:21', '2010-09-23 12:07:49', 0, NULL, 1, 2);
INSERT INTO `users` VALUES (3, 'raju', 'raju@gmail.com', 'raju', 'raju', 'raju', 'raju infotech', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '0342c881303dfa0911b9c7028ca6ec6ce792be91404be30093c1ff920b02f239658f4b88c9f7891ad994d3191c4b9b3d982eb8dfe64b9b7e1160794b1ce550a0', '8NnAdXceGMJuaohR0lzV', '9811529396ab32f34a53a630a903bde97ecea56deac33149fd84420794bf416cdfb2092d0f9cec7a5285f94c8ac747b26eeab972c0901c3498ab187fbb26d398', 'GTi3sjAESJlA1bjjkld7', '2010-09-17 09:00:30', NULL, '2010-09-17 07:11:19', NULL, '172.20.1.33', 1, NULL, '2010-09-17 07:09:03', '2010-09-17 09:00:30', 0, NULL, 3, NULL);

-- --------------------------------------------------------

-- 
-- Table structure for table `vendor_types`
-- 

CREATE TABLE `vendor_types` (
  `id` int(11) NOT NULL auto_increment,
  `title` varchar(36) collate utf8_unicode_ci default NULL,
  `user_id` int(11) default '0',
  `created_at` datetime default NULL,
  `updated_at` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=7 ;

-- 
-- Dumping data for table `vendor_types`
-- 

INSERT INTO `vendor_types` VALUES (1, 'Photographer', 0, '2010-09-15 12:25:34', '2010-09-15 12:25:34');
INSERT INTO `vendor_types` VALUES (2, 'Website', 0, '2010-09-15 12:25:34', '2010-09-15 12:25:34');
INSERT INTO `vendor_types` VALUES (3, 'Signs', 0, '2010-09-15 12:25:34', '2010-09-15 12:25:34');
INSERT INTO `vendor_types` VALUES (4, 'my own', 1, '2010-09-15 13:02:24', '2010-09-15 13:02:24');
INSERT INTO `vendor_types` VALUES (5, 'mahesh', 1, '2010-09-15 13:10:32', '2010-09-15 13:10:32');
INSERT INTO `vendor_types` VALUES (6, 'xcvcvxvx', 1, '2010-09-16 12:35:58', '2010-09-16 12:35:58');
