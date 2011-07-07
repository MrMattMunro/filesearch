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
package com.searchlocal.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.searchlocal.bean.FileOpenerBean;
import com.searchlocal.bean.WordFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;

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
	 * 创建FileOpener表
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createFileOpenertable(String namespace) throws DBException,
			LogicException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String sql = SqlUtil.getSqlbyId("createFileOpener");
		try {
			success = execute(sql, conn);
		} catch (DBException e) {
			logger.error("DB_E023", sql, e);
			throw new DBException("DB_E023", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 取出FileOpener纪录
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<FileOpenerBean> getFileOpener(String namespace) throws LogicException,
			DBException {
		Connection conn = BaseDao.getBaseConn(namespace);
		// SQL语句
		String sql = SqlUtil.getSqlbyId("selectFileOpener");
		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		try {
			setReadOnly(conn);
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
        String sql = SqlUtil.getSqlbyId("selectFileOpenerByType");
		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		try {
			setReadOnly(conn);
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

	/**
	 * 插入FileOpener记录
	 * 
	 * @param beanList FileOpener数据
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertFileOpenRecord(List<FileOpenerBean> beanList, String namespace)
			throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String sql = SqlUtil.getSqlbyId("insertFileOpenRecord");
		PreparedStatement stmt;
		FileOpenerBean element;
		try {
			for (Iterator<FileOpenerBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (FileOpenerBean) iter.next();
				stmt = conn.prepareStatement(sql);
				if (null != element) {
					stmt.setString(1, element.getFileType());
					stmt.setString(2, element.getExePath());
					stmt.setTimestamp(3, new Timestamp(new Date().getTime()));
				}
				if (stmt != null) {
				    stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			// String param = SQLParameterUtil.getBeanToString(element);
			// logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E024", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return true;
	}
}
