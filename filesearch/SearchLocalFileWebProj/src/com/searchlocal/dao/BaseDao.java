/**
 * $RCSfile: BaseDao.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.dao;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.dbpool.CommonsDBCP;
import com.web.searchlocal.dbpool.ConnectionParam;
import com.web.searchlocal.exception.DBException;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.util.CLogger;
import com.web.searchlocal.util.SQLParameterUtil;
import com.web.searchlocal.util.WebSqlUtil;

/**
 * DB连接操作基类
 * 
 * <p>Title:DB连接操作基类 </p>
 * <p>Description: DB的共通操作</p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class BaseDao {
	
	/** 日志 */
	private static CLogger logger = new CLogger(BaseDao.class);

	private static CommonsDBCP basedbcp = null;
	
	private static CommonsDBCP dbcp = null;

	final private static String BASE_DB_SOURCCE = Constant.path
			+ "com\\web\\searchlocal\\properties\\basedataSource.properties";

	final private static String DB_SOURCCE = Constant.path
			+ "com\\web\\searchlocal\\properties\\dataSource.properties";

	/**
	 * 创建DB
	 * 
	 * @param namespace 数据库名称
	 * @throws LogicException
	 * @throws SQLException
	 */
	public static boolean createDataBase(String namespace) throws DBException, LogicException {
		ConnectionParam connparam = getConnParam(BASE_DB_SOURCCE);

		String sql = "";
		Connection conn = null;
		Statement stmt = null;
		try {
			Class.forName(connparam.getDriver());
			conn = DriverManager.getConnection(connparam.getUrl());

			// 生成SQL
			String presql = WebSqlUtil.getSqlbyId("createDatabase");
			Map<String, String> paramMap = new HashMap<String, String>();
			paramMap.put("namespace", namespace);
			sql = SQLParameterUtil.convertSQL(presql, paramMap);
			stmt = conn.createStatement();
			return stmt.execute(sql);
		} catch (ClassNotFoundException e) {
			logger.error("DB_E030", sql, namespace, e);
			throw new DBException("DB_E030", e);
		} catch (SQLException e) {
			logger.error("DB_E029", sql, namespace, e);
			throw new DBException("DB_E029", e);
		} finally {
			closeConnection(null, stmt, conn);
		}
	}

	/**
	 * 销毁DB
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public static boolean dropDataBase(String namespace) throws DBException, LogicException {
		ConnectionParam connparam = getConnParam(BASE_DB_SOURCCE);
		String sql = "";
		try {
			Class.forName(connparam.getDriver());
			Connection conn = DriverManager.getConnection(connparam.getUrl());

			// 生成SQL
			String presql = WebSqlUtil.getSqlbyId("dropDatabase");
			Map<String, String> paramMap = new HashMap<String, String>();
			paramMap.put("namespace", namespace);
			sql = SQLParameterUtil.convertSQL(presql, paramMap);
			Statement stmt;
			stmt = conn.createStatement();
			return stmt.execute(sql);
		} catch (ClassNotFoundException e) {
			logger.error("DB_E030", sql, namespace, e);
			throw new DBException("DB_E030", e);
		} catch (SQLException e) {
			logger.error("DB_E029", sql, namespace, e);
			throw new DBException("DB_E029", e);
		}
	}

	/**
	 * 取得与DB的连接。
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public static Connection getBaseConn(String namespace) throws LogicException, DBException {
		ConnectionParam connparam = getConnParam(BASE_DB_SOURCCE);
		Connection conn;
		basedbcp = new CommonsDBCP(connparam);
		try {
			conn = basedbcp.getConn();
		} catch (SQLException e) {
			logger.error("DB_E028", e);
			throw new DBException("DB_E028", e);
		}
		return conn;
	}
	
	/**
	 * 取得与DB的连接。
	 * 
	 * @param namespace 数据库名称
	 * @throws DBException
	 * @throws LogicException
	 */
	public static Connection getConn(String namespace) throws LogicException, DBException {
		ConnectionParam connparam = getConnParam(DB_SOURCCE);
		Connection conn;
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		String url = SQLParameterUtil.convertSQL(connparam.getUrl(), paramMap);
		connparam.setUrl(url);
		dbcp = new CommonsDBCP(connparam);
		try {
			conn = dbcp.getConn();
		} catch (SQLException e) {
			logger.error("DB_E028", e);
			throw new DBException("DB_E028", e);
		}
		return conn;
	}

	/**
	 * 取得与DB的连接的参数
	 * 
	 * @param propfilepath 配置文件位置
	 * @return ConnectionParam 配置对象
	 * @throws LogicException
	 */
	private static ConnectionParam getConnParam(String propfilepath) throws LogicException {
		Properties prop = new Properties();
		FileInputStream in;
		try {
			in = new FileInputStream(propfilepath);
			prop.load(in);
		} catch (FileNotFoundException e) {
			logger.error("LG_E001", propfilepath);
			throw new LogicException("LG_E001", e);
		} catch (IOException e) {
			logger.error("LG_E003", propfilepath);
			throw new LogicException("LG_E003", e);
		}

		String user = prop.get(Constant.DBConstansInfo.DATABASE_USER).toString();
		String password = prop.get(Constant.DBConstansInfo.DATABASE_PASSWORD).toString();
		String driver = prop.get(Constant.DBConstansInfo.DATABASE_CLASS_FOR_NAME).toString();
		String url = prop.get(Constant.DBConstansInfo.DATABASE_URL).toString();
		url = url + "&user=" + user + "&password=" + password;

		ConnectionParam param = new ConnectionParam(driver, url, user, password);
		return param;
	}

	/**
	 * 删除对应数据库，表里，对应文件路径纪录
	 * 
	 * @param namespace 数据库名称
	 * @param table 表名
	 * @param path 文件路径
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean deleteRecordByPath(String namespace, String table, String path)
			throws DBException, LogicException {
		Connection conn = BaseDao.getBaseConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = WebSqlUtil.getSqlbyId("deleteRecordByPath");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		paramMap.put("table", table);

		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		logger.debug("sql:" + sql);

		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			stmt.setString(1, path);
			success = stmt.execute();
		} catch (SQLException e) {
			logger.error("DB_E023", sql, e);
			throw new DBException("DB_E023", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}
	
	/**
	 * 取得执行查询sql的结果集
	 * 
	 * @param sql 执行SQL
	 * @param path 文件路径
	 * @param conn DB连接
	 * @return ResultSet 结果集
	 * @throws DBException
	 */
	public static ResultSet executeQuerySQL(String sql, String path, Connection conn)
			throws DBException {
		ResultSet rs;
		try {
			PreparedStatement stmt = conn.prepareStatement(sql);
			stmt.setString(1, path);
			rs = stmt.executeQuery();
		} catch (SQLException e) {
			logger.error("DB_E001", sql, e);
			throw new DBException("DB_E001", e);
		}
		return rs;
	}

	/**
	 * 执行sql
	 * 
	 * @param sql 执行SQL
	 * @param conn DB连接
	 * @return boolean 是否更新成功
	 * @throws DBException
	 */
	public static boolean execute(String sql, Connection conn) throws DBException {
		boolean sucess = false;
		try {
			Statement stmt = conn.prepareStatement(sql);
			sucess = stmt.execute(sql);
		} catch (SQLException e) {
			logger.error("DB_E001", sql, e);
			throw new DBException("DB_E001", e);
		}
		return sucess;
	}

	/**
	 * 打开事务
	 * 
	 * @param conn DB连接
	 */
	public static void openTransaction(Connection conn) throws DBException {
		if (conn != null) {
			try {
				if (conn.getAutoCommit()) {
					conn.setAutoCommit(false);
				}
			} catch (SQLException e) {
				logger.error("DB_E002", e);
				throw new DBException("DB_E002", e);
			}
		}
	}

	/**
	 * 关闭与DB的连接
	 * 
	 * @param conn Connection 数据库连接
	 * @param stmt Statement 上下文
	 * @param rs ResultSet 结果集
	 * @throws DBException
	 */
	public static void closeConnection(ResultSet rs, Statement stmt, Connection conn)
			throws DBException {
		if (rs != null) {
			try {
				rs.close();
				rs = null;
			} catch (SQLException e) {
				rs = null;
				logger.error("DB_E003", e);
				throw new DBException("DB_E003", e);
			}
		}
		if (stmt != null) {
			try {
				stmt.close();
				stmt = null;
			} catch (SQLException e) {
				stmt = null;
				logger.error("DB_E003", e);
				throw new DBException("DB_E003", e);
			}
		}
		if (conn != null) {
			try {
				conn.close();
				conn = null;
			} catch (SQLException e) {
				conn = null;
				logger.error("DB_E003", e);
				throw new DBException("DB_E003", e);
			}
		}
	}

	/**
	 * 事务提交
	 * 
	 * @throws DBException
	 * 
	 */
	public boolean commit(Connection conn) throws DBException {
		try {
			conn.commit();
			return true;
		} catch (SQLException e) {
			logger.error("DB_E004", e);
			throw new DBException("DB_E004", e);
		}
	}

	/**
	 * 事务回滚
	 * 
	 * @throws DBException
	 * 
	 */
	public boolean rollback(Connection conn) throws DBException {
		try {
			conn.rollback();
			return true;
		} catch (SQLException e) {
			logger.error("DB_E005", e);
			throw new DBException("DB_E005", e);
		}
	}

}