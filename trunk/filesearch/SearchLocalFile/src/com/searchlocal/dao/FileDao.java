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

import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.FileParam;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

public class FileDao extends BaseDao {

	private static CLogger logger = new CLogger(FileDao.class);

	public FileDao() {

	}

	/**
	 * 插入文件的更新操作
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws DBException
	 */
	public synchronized static void executeFileUpdateSQL(Connection conn,
			String sql, List elementList) throws DBException {
		FileParam element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			conn.setReadOnly(false);
			for (Iterator iter = elementList.iterator(); iter.hasNext();) {
				element = (FileParam) iter.next();
				if (null != element) {
					stmt.setString(1, element.getPath());
					stmt.setTimestamp(2, new Timestamp(element.getLastModify()));
					stmt.setString(3, element.getError());
				}
				if (stmt != null) {
					stmt.executeUpdate();
				}
			}
		} catch (SQLException e) {
			// String param = SQLParameterUtil.getBeanToString(element);
			// logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E022", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 删除File纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 * @throws LogicException
	 */
	public synchronized boolean deleteFileRecord(String namespace, String path)
			throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String sql = SqlUtil.getsql(namespace, "deleteFileRecord");
		logger.debug("sql:" + sql);
		try {
			PreparedStatement stmt = conn.prepareStatement(sql);
			stmt.setString(1, path);
			success = stmt.execute();
		} catch (Exception e) {
			logger.error("DB_E023", sql, e);
			throw new DBException("DB_E023", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 删除对应数据库，表里，对应文件路径纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 * @throws LogicException
	 */
	public synchronized boolean deleteRecordByPath(String namespace,
			String table, String path) throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("deleteRecordByPath");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);
		paramMap.put("table", table);

		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		logger.debug("sql:" + sql);
		
		PreparedStatement stmt;
		try {
			conn.setReadOnly(false);
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
	 * 创建File表
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 * @throws LogicException
	 */
	public synchronized boolean createFiletable(String namesapce)
			throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createFileRecord");
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
	 * 取出File纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized List<FileParam> getFileRecord(String namespace)
			throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("selectFileRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);

		List<FileParam> returnList = new ArrayList<FileParam>();
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			setReadOnly(conn);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);
			
			while (rs.next()) {
				FileParam param = new FileParam();
				param.setPath(rs.getString("path"));
				param.setLastModify(rs.getTimestamp("lastmodify").getTime());
				param.setError(rs.getString("error"));
				returnList.add(param);
			}
		} catch (SQLException e) {
			throw new DBException("DB_E024", e);
		}
		closeConnection(null, null, conn);
		return returnList;
	}

	/**
	 * 插入File纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean insertFileRecord(List beanList, String namespace)
			throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);

		// SQL语句
		String presql = SqlUtil.getSqlbyId("insertFileRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namespace);

		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			conn.setReadOnly(false);
			executeFileUpdateSQL(conn, sql, beanList);
		} catch (DBException e) {
			// String param = SQLParameterUtil.getBeanToString(element);
			// logger.error("DB_E022", sql, param, e);
			throw new DBException("DB_E024", e);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		commit(conn);
		closeConnection(null, null, conn);
		return true;
	}

	/**
	 * 更新File纪录
	 * 
	 * @return ResultSet
	 * @throws DBException
	 * @throws LogicException
	 * @throws DBException
	 * @throws DBException
	 * @throws LogicException
	 */
	public synchronized boolean updateFileRecord(List beanList, String namespace)
			throws LogicException, DBException {

		Connection conn = BaseDao.getConn(namespace);
		openTransaction(conn);
		// SQL语句
		String presql = SqlUtil.getSqlbyId("updateFileRecord");

		PreparedStatement stmt;
		FileParam element;

		try {
			for (Iterator iter = beanList.iterator(); iter.hasNext();) {
				element = (FileParam) iter.next();

				Map<String, String> paramMap = new HashMap<String, String>();
				paramMap.put("namespace", namespace);

				String sql = SQLParameterUtil.convertSQL(presql, paramMap);
				
				stmt = conn.prepareStatement(sql);

				if (null != element) {
					stmt.setTimestamp(1, new Timestamp(element.getLastModify()));
					stmt.setString(2, element.getError());
					stmt.setString(3, element.getPath());
			
				}
				int row = 0;
				if (stmt != null) {
					row = stmt.executeUpdate();
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

	public boolean execbatch(String datapath, String namesapce)
			throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		Statement st = null;
		try {
			st = conn.createStatement();
			String sql = "Load Data InFile " + datapath
					+ " Into Table t_file FIELDS TERMINATED BY ','";
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
