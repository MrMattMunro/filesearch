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
	 * @param namespace db名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean createFileOpenertable(String namespace) throws DBException,
			LogicException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createFileOpener");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
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
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<FileOpenerBean> getFileOpener(String namespace) throws LogicException,
			DBException {
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectFileOpener");
		Map<String, String> paramMap = new HashMap<String, String>();

		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
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
	 * 插入FileOpener记录
	 * 
	 * @param beanList FileOpener数据
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean insertFileOpenRecord(List<FileOpenerBean> beanList, String namespace)
			throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("insertFileOpenRecord");
		PreparedStatement stmt;
		FileOpenerBean element;
		try {
			for (Iterator<FileOpenerBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (FileOpenerBean) iter.next();
				Map<String, String> paramMap = new HashMap<String, String>();
				paramMap.put("namespace", namespace);

				String sql = SQLParameterUtil.convertSQL(presql, paramMap);
				stmt = conn.prepareStatement(sql);
				if (null != element) {
					stmt.setString(1, element.getFileType());
					stmt.setString(2, element.getExePath());
					stmt.setTimestamp(3, new Timestamp(new Date().getTime()));
				}
				int row;
				if (stmt != null) {
					row = stmt.executeUpdate();
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
