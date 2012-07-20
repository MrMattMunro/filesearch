CREATE TABLE `mf_friends_email` (
  `user_email` varchar(100) NOT NULL default '',
  `friends_email` varchar(1200) default NULL,
  PRIMARY KEY  (`user_email`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8