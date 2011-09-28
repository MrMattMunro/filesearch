/**
 * $RCSfile: SearcherDao.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.web.searchlocal.bean.FileOpenerBean;
import com.web.searchlocal.exception.DBException;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.util.CLogger;
import com.web.searchlocal.util.WebSqlUtil;

/**
 * 文件打开对象Dao
 * 
 * <p>Title: 文件打开对象Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileOpenerDao extends BaseDao{

	/** 日志 */
	private static CLogger logger = new CLogger(FileOpenerDao.class);
	
	
	/**
	 * 取出FileOpener纪录
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<FileOpenerBean> getFileOpener(Connection conn) throws LogicException,
			DBException {
		// SQL语句
		String sql = WebSqlUtil.getSqlbyId("selectFileOpener");
		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);

			while (rs.next()) {
				FileOpenerBean bean = new FileOpenerBean();
				bean.setId(rs.getString("id"));
				bean.setFileType(rs.getString("filetype"));
				bean.setExePath(rs.getString("exepath"));
				bean.setLastmodify(rs.getTimestamp("lastmodify").getTime());
				returnList.add(bean);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(null, null, conn);
		return returnList;
	}
	
	/**
	 * 取出FileOpener纪录
	 * 
	 * @param namespace 数据库名称
     * @param fileType 文件类型
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<FileOpenerBean> getFileOpenerByFileType(String namespace, String filetype) throws LogicException,
			DBException {
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
        String sql = WebSqlUtil.getSqlbyId("selectFileOpenerByType");
		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		try {
			PreparedStatement stmt = conn.prepareStatement(sql);
			stmt.setString(1, filetype);
			// 结果集
			ResultSet rs = stmt.executeQuery();
			while (rs.next()) {
				FileOpenerBean bean = new FileOpenerBean();
				bean.setFileType(rs.getString("filetype"));
				bean.setExePath(rs.getString("exepath"));
				returnList.add(bean);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(null, null, conn);
		return returnList;
	}
}
