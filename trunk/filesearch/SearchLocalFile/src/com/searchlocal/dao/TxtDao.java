/**
 * $RCSfile: TxtDao.java
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

import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * Txt文件以及代码Dao
 * 
 * <p>Title: Txt文件以及代码Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class TxtDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(TxtDao.class);

	/**
	 * 构造器
	 */
	public TxtDao() {
		
	}

	/**
	 * 执行Txt的更新操作
	 * 
	 * @param conn 数据库连接
	 * @param sql SQL语句
	 * @param elementList 文件对象列表
	 * @throws DBException
	 */
	public static void executeTxtUpdateSQL(Connection conn, String sql,
			List<TxtFileBean> elementList) throws DBException {
		TxtFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator<TxtFileBean> iter = elementList.iterator(); iter.hasNext();) {
				element = (TxtFileBean) iter.next();
				if (null != element) {
					stmt.setString(1, element.getFilename());
					stmt.setString(2, element.getPath());
					stmt.setTimestamp(3, new Timestamp(element.getLastmodify()));
					stmt.setString(4, element.getContent());
					stmt.setInt(5, new Integer(element.getRownb()));
				}
				if (stmt != null) {
					stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E022", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 创建Txt表
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean createTxttable(String namespace) throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createTxtRecord");
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
	 * 插入Txt纪录
	 * 
	 * @param beanList Ppt文件数据
	 * @param filepath 文件路径
	 * @param lastmodify 最后修改时间
	 * @param filename 文件名称
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertTxtRecord(List<TxtFileBean> beanList, String filepath, long lastmodify,
			String filename, String namespace) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("insertTxtRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);

		TxtFileBean element = null;
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			conn.setReadOnly(false);
			for (Iterator<TxtFileBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (TxtFileBean) iter.next();
				element.setFilename(filename);
				element.setLastmodify(lastmodify);
				element.setPath(filepath);
			}
			executeTxtUpdateSQL(conn, sql, beanList);

		} catch (Exception e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E024", e);
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
					+ " Into Table t_txt FIELDS TERMINATED BY ','";
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
