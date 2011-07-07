/**
 * $RCSfile: ChmDao.java
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

import com.searchlocal.bean.ChmFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * Chm文件操作Dao
 * 
 * <p>Title: Chm文件操作Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChmDao extends BaseDao {
	
	/** 日志 */
	private static CLogger logger = new CLogger(ChmDao.class);

	/** 
	 * 构造器
	 */
	public ChmDao() throws DBException {
	}

	/**
	 * 执行Chm的更新操作
	 * 
	 * @param conn DB连接
	 * @param sql 更新SQL
	 * @param elementList Chm文件记录列表
	 * @throws DBException
	 */
	public static void executeChmUpdateSQL(Connection conn, String sql, List<ChmFileBean> elementList)
			throws DBException {
		ChmFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator<ChmFileBean> iter = elementList.iterator(); iter.hasNext();) {
				element = (ChmFileBean) iter.next();
				stmt.setString(1, element.getFilename());
				stmt.setString(2, element.getPath());
				stmt.setTimestamp(3, new Timestamp(element.getLastmodify()));
				stmt.setString(4, element.getContent());
				stmt.setString(5, element.getCatalogname());

				if (stmt != null) {
					stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E007", sql, param, e);
			throw new DBException("DB_E007", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 创建Chm表
	 * 
	 * @param namesapce 数据库
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createChmtable(String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createChmRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			success = execute(sql, conn);
		} catch (DBException e) {
			logger.error("DB_E008", sql);
			throw new DBException("DB_E008", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 插入Chm记录
	 * 
	 * @param beanList Chm文件Bean列表
	 * @param filepath 文件路径
	 * @param filename 文件名称
     * @param lastmodify 最后更新时间
	 * @param namesapce 数据库
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertChmRecord(List<ChmFileBean> beanList, String filepath, long lastmodify,
			String filename, String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getBaseConn(namesapce);
		openTransaction(conn);
		// 取出Sql
		String presql = SqlUtil.getSqlbyId("insertChmRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		ChmFileBean element = null;
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			conn.setReadOnly(false);
			for (Iterator<ChmFileBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (ChmFileBean) iter.next();
				element.setFilename(filename);
				element.setLastmodify(lastmodify);
				element.setPath(filepath);
			}
			executeChmUpdateSQL(conn, sql, beanList);
		} catch (Exception e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E009", sql, param, e);
			throw new DBException("DB_E009", e);
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
		Connection conn = BaseDao.getBaseConn(namesapce);
		openTransaction(conn);
		Statement st = null;
		try {
			st = conn.createStatement();
			String sql = "Load Data InFile " + datapath
					+ " Into Table t_chm FIELDS TERMINATED BY ','";
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
