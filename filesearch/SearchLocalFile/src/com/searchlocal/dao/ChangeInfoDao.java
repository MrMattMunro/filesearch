/**
 * $RCSfile: ChangeInfoDao.java
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
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.searchlocal.bean.ChangInfoBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;

/**
 * 目录变化的文件Dao
 * 
 * <p>Title: 目录变化的文件Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChangeInfoDao extends BaseDao {
	
	/** 日志 */
	private static CLogger logger = new CLogger(ChangeInfoDao.class);

	/** 
	 * 构造器
	 */
	public ChangeInfoDao() {

	}

	/**
	 * 创建ChangeInfo表
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean createChangeInfotable(String namesapce) throws DBException,
			LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createChangeInfo");
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
	 * 取出记录变更纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<ChangInfoBean> getChangeInfoByHasoper(String namespace, 
			 String hasoper) throws LogicException,
			DBException {
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectChangeInfoByHasoper");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		paramMap.put("hasoper", hasoper);

		List<ChangInfoBean> returnList = new ArrayList<ChangInfoBean>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			setReadOnly(conn);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);

			while (rs.next()) {
				ChangInfoBean bean = new ChangInfoBean();
				bean.setId(rs.getString("id"));
				bean.setOperflg(rs.getString("operflg"));
				bean.setHasoper(rs.getString("hasoper"));
				bean.setPath(rs.getString("path"));
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
	 * 更新File纪录
	 * 
	 * @param beanList 变化文件记录列表
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean updateChangeInfo(List<ChangInfoBean> beanList, String namespace)
			throws LogicException, DBException {

		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("updateChangeInfo");

		PreparedStatement stmt;
		ChangInfoBean element;
		try {
			for (Iterator<ChangInfoBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (ChangInfoBean) iter.next();
				Map<String, String> paramMap = new HashMap<String, String>();
				paramMap.put("namespace", namespace);

				String sql = SQLParameterUtil.convertSQL(presql, paramMap);

				stmt = conn.prepareStatement(sql);
				if (null != element) {
					stmt.setTimestamp(1, new Timestamp(element.getLastmodify()));
					stmt.setString(2, element.getHasoper());
					stmt.setString(3, element.getPath());
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