/**
 * $RCSfile: WordDao.java
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
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.searchlocal.bean.WordFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * Word文件Dao
 * 
 * <p>Title: Word文件Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class WordDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(WordDao.class);

	/**
	 * 构造器
	 */
	public WordDao() {
	}

	/**
	 * 执行Word的更新操作
	 * 
	 * @param conn 数据库连接
	 * @param sql SQL语句
	 * @param elementList 文件对象列表
	 * @throws DBException
	 * @throws DBException
	 */
	public static void executeWordUpdateSQL(Connection conn, String sql, List<WordFileBean> elementList)
			throws DBException {
		WordFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator<WordFileBean> iter = elementList.iterator(); iter.hasNext();) {
				element = (WordFileBean) iter.next();
				stmt.setString(1, element.getFilename());
				stmt.setString(2, element.getPath());
				stmt.setTimestamp(3, new Timestamp(element.getLastmodify()));
				stmt.setString(4, element.getContent());
				stmt.setInt(5, new Integer(element.getParagraphNo()));

				if (stmt != null) {
					stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E025", sql, param, e);
			throw new DBException("DB_E025", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 创建Word表
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createWordtable(String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createWordRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			success = execute(sql, conn);
		} catch (DBException e) {
			logger.error("DB_E026", sql, e);
			throw new DBException("DB_E026", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 插入Word记录
	 * 
	 * @param beanList Ppt文件数据
	 * @param filepath 文件路径
	 * @param lastmodify 最后修改时间
	 * @param filename 文件名称
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertWordRecord(List<WordFileBean> beanList, String filepath, long lastmodify,
			String filename, String namesapce) throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namesapce);

		String presql = SqlUtil.getSqlbyId("insertWordRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);

		WordFileBean element = null;
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			conn.setReadOnly(false);
			openTransaction(conn);
			for (Iterator<WordFileBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (WordFileBean) iter.next();
				element.setFilename(filename);
				element.setLastmodify(lastmodify);
				element.setPath(filepath);
			}
			executeWordUpdateSQL(conn, sql, beanList);
		} catch (Exception e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E027", sql, param, e);
			throw new DBException("DB_E027", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return true;
	}

	/**
	 * 执行Batch文件
	 * 
	 * @param datapath csv文件路径
     * @param namesapce 数据库
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean execbatch(String datapath, String namesapce) throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		Statement st = null;
		try {
			st = conn.createStatement();
			String sql = "Load Data InFile " + datapath
					+ " Into Table t_word FIELDS TERMINATED BY ','";
			sql = StringUtils.editSQL(sql);
			st.execute(sql);
		} catch (SQLException e) {
			throw new DBException("DB_E027", e);
		}
		commit(conn);
		closeConnection(null, st, conn);
		return true;
	}
}
