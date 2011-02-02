/**
 * $RCSfile: ResultDao.java
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
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.searchlocal.bean.ResultBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;

/**
 * 检索结果Dao
 * 
 * <p>Title: 检索结果Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ResultDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(ResultDao.class);

	/**
	 * 构造器
	 */
	public ResultDao() {
	}

	/**
	 * 创建检索结果表
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean createResulttable(String namesapce) throws DBException,
			LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createResult");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
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
	 * 插入Result记录
	 * 
	 * @param beanList FileOpener数据
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean insertResultRecord(List<ResultBean> beanList, String namespace)
			throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("insertResultRecord");

		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		PreparedStatement stmt;
		ResultBean element;
		try {
			for (Iterator<ResultBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (ResultBean) iter.next();
				stmt = conn.prepareStatement(sql);
				if (null != element) {
					stmt.setString(1, element.getFileType());
					stmt.setString(2, element.getFilePath());
					stmt.setString(3, element.getDesp());
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

	/**
	 * 删除搜索结果记录
	 * 
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean deleteResultRecord(String namespace) throws LogicException,
			DBException {
		// 取得连接
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("deleteResultRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		// 删除结果记录
		execute(sql, conn);

		commit(conn);
		closeConnection(null, null, conn);
		return true;
	}

}