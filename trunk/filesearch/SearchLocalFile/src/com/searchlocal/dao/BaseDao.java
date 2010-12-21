package com.searchlocal.dao;

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

import com.searchlocal.constants.Constant;
import com.searchlocal.dbpool.CommonsDBCP;
import com.searchlocal.dbpool.ConnectionParam;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;

/**
 * DB连接操作基类
 * 
 * @author changsong qianjinfu@gmail.com
 * @version $Revision 1.0$
 */
public class BaseDao {

	private static CLogger logger = new CLogger(BaseDao.class);

	private static CommonsDBCP commdbcp = null;

	final private static String BASE_DB_SOURCCE = Constant.path
			+ "com\\searchlocal\\properties\\basedataSource.properties";

	final private static String DB_SOURCCE = Constant.path
			+ "com\\searchlocal\\properties\\dataSource.properties";

	/**
	 * 创建DB
	 * 
	 * @return Connection
	 * @throws DBException
	 * @throws LogicException
	 * @throws SQLException
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public static boolean createDataBase(String namespace) throws DBException,
			LogicException {
		ConnectionParam connparam = getConnParam(BASE_DB_SOURCCE);

		String sql = "";
		Connection conn = null;
		Statement stmt = null;
		try {
			Class.forName(connparam.getDriver());
			conn = DriverManager.getConnection(connparam.getUrl());

			// 生成SQL
			String presql = SqlUtil.getSqlbyId("createDatabase");
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
	 * @return Connection
	 * @throws DBException
	 * @throws LogicException
	 * @throws SQLException
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public static boolean dropDataBase(String namespace) throws DBException,
			LogicException {
		ConnectionParam connparam = getConnParam(BASE_DB_SOURCCE);
		String sql = "";
		try {
			Class.forName(connparam.getDriver());
			Connection conn = DriverManager.getConnection(connparam.getUrl());

			// 生成SQL
			String presql = SqlUtil.getSqlbyId("dropDatabase");
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
	 * @return Connection
	 * @throws LogicException
	 * @throws DBException
	 * @throws DBException
	 * @throws SQLException
	 * @throws IOException
	 */
	public static Connection getConn(String namespace) throws LogicException,
			DBException {
		ConnectionParam connparam = getConnParam(DB_SOURCCE);

		Connection conn;
		if (commdbcp == null) {
			Map<String, String> paramMap = new HashMap<String, String>();
			paramMap.put("namespace", namespace);
			String url = SQLParameterUtil.convertSQL(connparam.getUrl(),
					paramMap);
			connparam.setUrl(url);
			commdbcp = new CommonsDBCP(connparam);
		}

		try {
			conn = commdbcp.getConn();
		} catch (SQLException e) {
			logger.error("DB_E028", e);
			throw new DBException("DB_E028", e);
		}
		return conn;
	}

	private static ConnectionParam getConnParam(String propfilepath)
			throws LogicException {

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

		String user = prop.get(Constant.DBConstansInfo.DATABASE_USER)
				.toString();
		String password = prop.get(Constant.DBConstansInfo.DATABASE_PASSWORD)
				.toString();
		String driver = prop.get(
				Constant.DBConstansInfo.DATABASE_CLASS_FOR_NAME).toString();
		String url = prop.get(Constant.DBConstansInfo.DATABASE_URL).toString();
		url = url + "&user=" + user + "&password=" + password;

		ConnectionParam param = new ConnectionParam(driver, url, user, password);

		return param;
	}

	/**
	 * 取得执行查询sql的结果集
	 * 
	 * @return ResultSet
	 * @throws DBException
	 */
	public static ResultSet executeQuerySQL(String sql, String path, Connection conn)
			throws DBException {
		ResultSet rs;
		try {
			setReadOnly(conn);
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
	 * @return ResultSet
	 * @throws DBException
	 */
	public static boolean execute(String sql, Connection conn)
			throws DBException {
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
	 * 打开事务出错
	 * 
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
	 * @param conn
	 *            Connection
	 * @param stmt
	 *            Statement
	 * @param rs
	 *            ResultSet
	 * @throws DBException
	 */
	public static void closeConnection(ResultSet rs, Statement stmt,
			Connection conn) throws DBException {
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

	/**
	 * 设置DB的只读模式
	 * 
	 * @throws DBException
	 * 
	 */
	public static boolean setReadOnly(Connection conn) throws DBException {
		try {
			if (!conn.isReadOnly()) {
				conn.setReadOnly(true);
			}
			return true;
		} catch (SQLException e) {
			logger.error("DB_E006", e);
			throw new DBException("DB_E006", e);
		}
	}

	/**
	 * @return Returns the commdbcp.
	 */
	public static CommonsDBCP getCommdbcp() {
		return commdbcp;
	}
}