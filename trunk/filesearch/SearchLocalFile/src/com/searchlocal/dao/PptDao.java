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

public class PptDao extends BaseDao {

	private static CLogger logger = new CLogger(PptDao.class);

	public PptDao() {

	}

	/**
	 * 执行Ppt的更新操作
	 * 
	 * @return ResultSet
	 * @throws DBException
	 */
	public synchronized void executePptUpdateSQL(Connection conn, String sql, List elementList)
			throws DBException {
		PptFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator iter = elementList.iterator(); iter.hasNext();) {
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

	public synchronized boolean createPpttable(String namesapce) throws LogicException, DBException {
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

	public synchronized boolean insertPptRecord(List beanList, String filepath, long lastmodify,
			String filename, String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		// 
		String presql = SqlUtil.getSqlbyId("insertPptRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);

		PptFileBean element = null;
		try {
			conn.setReadOnly(false);
			for (Iterator iter = beanList.iterator(); iter.hasNext();) {
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

	public boolean execbatch(String datapath, String namesapce) throws DBException, LogicException {
		Connection conn = BaseDao.getConn(namesapce);
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
