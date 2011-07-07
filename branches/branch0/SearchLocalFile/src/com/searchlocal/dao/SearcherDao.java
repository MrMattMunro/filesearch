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
import java.util.List;
import java.util.Map;

import com.searchlocal.bean.SearcherBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;

/**
 * 搜索对象Dao
 * 
 * <p>Title: 搜索对象Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearcherDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(SearcherDao.class);
	
	/**
	 * 构造器
	 */
	public SearcherDao() {
	}

	/**
	 * 创建FileOpener表
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean createSearchertable(String namesapce) throws DBException,
			LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String sql = SqlUtil.getSqlbyId("createSearcher");
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
	 * 取出待建立索引的搜索对象
	 * 
     * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<SearcherBean> getNeedIndexSeacher(Connection conn)
			throws LogicException, DBException {
		// SQL语句
		String sql = SqlUtil.getSqlbyId("selectNeedIndexSeacher");
		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		Statement stmt = null;
		ResultSet rs = null;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(sql);
			while (rs.next()) {
				SearcherBean bean = new SearcherBean();
				bean.setId(rs.getString("id"));
				bean.setPath(rs.getString("path"));
				bean.setIndexPath(rs.getString("indexpath"));
				bean.setFileType(rs.getString("filetype"));
				bean.setLastmodify(rs.getTimestamp("lastmodify").getTime());
				returnList.add(bean);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(rs, stmt, null);
		return returnList;
	}
	
	/**
	 * 取出待建立索引的搜索对象
	 * 
	 * @param id 搜索对象的Id
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean deleteSearcher(String id) throws LogicException, DBException {
		// 取得连接
		Connection conn = BaseDao.getConn(Constant.CommonInfo.DATABASE);
		// SQL语句
		String sql = SqlUtil.getSqlbyId("deleteSearcherbyId");
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			stmt.setString(1, id);
			if (stmt != null) {
				stmt.executeUpdate();
			}
		} catch (SQLException e) {
			// String param = SQLParameterUtil.getBeanToString(element);
			// logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E024", e);
		}
		closeConnection(null, stmt, conn);
		return true;
	}
	
	/**
	 * 取出待删除索引的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public List<SearcherBean> getNeedDelSeacher(Connection conn)
			throws LogicException, DBException {
		// SQL语句
		String sql = SqlUtil.getSqlbyId("selectNeedDelSeacher");
		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		Statement stmt = null;
		ResultSet rs = null;
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(sql);
			while (rs.next()) {
				SearcherBean bean = new SearcherBean();
				bean.setId(rs.getString("id"));
				bean.setPath(rs.getString("path"));
				bean.setIndexPath(rs.getString("indexpath"));
				bean.setFileType(rs.getString("filetype"));
				bean.setLastmodify(rs.getTimestamp("lastmodify").getTime());
				returnList.add(bean);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(rs, stmt, null);
		return returnList;
	}

	/**
	 * 取出需要更新的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<SearcherBean> getNeedUpdateSeacher(Connection conn)
			throws LogicException, DBException {
		// SQL语句
		String sql = SqlUtil.getSqlbyId("selectNeedUpdateSeacher");
		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		Statement stmt = null;
		ResultSet rs = null;
		try {
			stmt = conn.createStatement();
		    rs = stmt.executeQuery(sql);
			while (rs.next()) {
				SearcherBean bean = new SearcherBean();
				bean.setId(rs.getString("id"));
				bean.setPath(rs.getString("path"));
				bean.setIndexPath(rs.getString("indexpath"));
				bean.setFileType(rs.getString("filetype"));
				bean.setLastmodify(rs.getTimestamp("lastmodify").getTime());
				returnList.add(bean);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(rs, stmt, null);
		return returnList;
	}
	
	/**
	 * 取出需要更新的搜索对象
	 * 
	 * @param conn 数据库连接
	 * @param bean 搜索对象
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean updateSearcherById(Connection conn, SearcherBean bean)
			throws LogicException, DBException {
		// SQL语句
		String sql = SqlUtil.getSqlbyId("updateSearcherById");
		PreparedStatement stmt;
		try {
				stmt = conn.prepareStatement(sql);
				if (null != bean) {
					stmt.setString(1, bean.getHasCreateIndex());
					stmt.setString(2, bean.getHasUpdate());
					stmt.setString(3, bean.getHasDel());
					stmt.setTimestamp(4, new Timestamp(new Date().getTime()));
					stmt.setString(5, bean.getId());
				}
				if (stmt != null) {
					stmt.executeUpdate();
				}
		} catch (SQLException e) {
			// String param = SQLParameterUtil.getBeanToString(element);
			// logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E024", e);
		}
		closeConnection(null, stmt, null);
		return true;
	}

}
