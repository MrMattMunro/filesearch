/**
 * $RCSfile: PptDao.java
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

import com.searchlocal.bean.PptFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * PptDao文件Dao
 * 
 * <p>Title: PptDao文件Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class PptDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(PptDao.class);
	
	/** 
	 * 构造器
	 */
	public PptDao() {

	}

	/**
	 * 执行Ppt的更新操作
	 * 
	 * @param conn db连接
	 * @param sql db连接
	 * @param elementList 文件对象列表
	 * @throws DBException
	 */
	public void executePptUpdateSQL(Connection conn, String sql, List<PptFileBean> elementList)
			throws DBException {
		PptFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator<PptFileBean> iter = elementList.iterator(); iter.hasNext();) {
				element = (PptFileBean) iter.next();
				stmt.setString(1, element.getFilename());
				stmt.setString(2, element.getPath());
				stmt.setTimestamp(3, new Timestamp(element.getLastmodify()));
				stmt.setString(4, element.getContent());
				stmt.setInt(5, new Integer(element.getPage()));
				if (stmt != null) {
					stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E019", sql, param, e);
			throw new DBException("DB_E019", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 创建Ppt表
	 * 
	 * @param namesapce 数据库名称
	 * @throws DBException
	 */
	public boolean createPpttable(String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createPptRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			success = execute(sql, conn);
		} catch (DBException e) {
			logger.error("DB_E020", sql, e);
			throw new DBException("DB_E020", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 插入Ppt记录
	 * 
	 * @param beanList Ppt文件数据
	 * @param filepath 文件路径
	 * @param lastmodify 最后修改时间
	 * @param filename 文件名称
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertPptRecord(List<PptFileBean> beanList, String filepath, long lastmodify,
			String filename, String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getBaseConn(namesapce);
		openTransaction(conn);
		// 取得Sql
		String presql = SqlUtil.getSqlbyId("insertPptRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);

		PptFileBean element = null;
		try {
			conn.setReadOnly(false);
			for (Iterator<PptFileBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (PptFileBean) iter.next();
				element.setFilename(filename);
				element.setLastmodify(lastmodify);
				element.setPath(filepath);
			}
			executePptUpdateSQL(conn, sql, beanList);
		} catch (Exception e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E021", sql, param, e);
			throw new DBException("DB_E021", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return true;
	}

	/**
	 * 执行Batch文件
	 * 
	 * @param datapath csv文件路径
	 * @param namespace 数据库名
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean execbatch(String datapath, String namesapce) throws DBException, LogicException {
		Connection conn = BaseDao.getBaseConn(namesapce);
		openTransaction(conn);
		Statement st = null;
		try {
			st = conn.createStatement();
			String sql = "Load Data InFile " + datapath
					+ " Into Table t_ppt FIELDS TERMINATED BY ','";
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
