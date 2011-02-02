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
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
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
		String presql = SqlUtil.getSqlbyId("createSearcher");
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
	 * 取出待建立索引的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<SearcherBean> getNeedIndexSeacher(String namespace)
			throws LogicException, DBException {
		// 取得连接
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectNeedIndexSeacher");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		// 待建立索引
		paramMap.put("hascreateindex", Constant.HasCreateIndexFlg.HAS_NO_CREAT_INDEX);

		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			setReadOnly(conn);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);

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
		closeConnection(null, null, conn);
		return returnList;
	}

	/**
	 * 取出待删除索引的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<SearcherBean> getNeedDelSeacher(String namespace)
			throws LogicException, DBException {
		// 取得连接
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectNeedDelSeacher");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		// 待删除索引
		paramMap.put("hasdel", Constant.HasDelFlg.HAS_DEL);

		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			setReadOnly(conn);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);
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
		closeConnection(null, null, conn);
		return returnList;
	}

	/**
	 * 取出需要更新的搜索对象
	 * 
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<SearcherBean> getNeedUpdateSeacher(String namespace)
			throws LogicException, DBException {
		// 取得连接
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectNeedUpdateSeacher");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		// 待更新索引
		paramMap.put("hasupdate", Constant.HasUpdateFlg.HAS_NOT_UPATE);

		List<SearcherBean> returnList = new ArrayList<SearcherBean>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			setReadOnly(conn);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);
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
		closeConnection(null, null, conn);
		return returnList;
	}

}
