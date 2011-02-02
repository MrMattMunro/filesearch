/**
 * $RCSfile: PdfDao.java
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

import com.searchlocal.bean.PdfFileBean;
import com.searchlocal.exception.DBException;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.SQLParameterUtil;
import com.searchlocal.util.SqlUtil;
import com.searchlocal.util.StringUtils;

/**
 * Pdf文件Dao
 * 
 * <p>Title: Pdf文件Dao</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class PdfDao extends BaseDao {

	/** 日志 */
	private static CLogger logger = new CLogger(PdfDao.class);

	/** 
	 * 构造器
	 */
	public PdfDao() {
	}

	/**
	 * 执行Pdf的更新操作
	 * 
	 * @param conn 数据库连接
	 * @param sql SQL语句
	 * @param elementList 文件对象列表
	 * @throws DBException
	 */
	public static void executePdfUpdateSQL(Connection conn, String sql, List<PdfFileBean> elementList)
			throws DBException {
		PdfFileBean element = null;
		PreparedStatement stmt;
		try {
			stmt = conn.prepareStatement(sql);
			for (Iterator<PdfFileBean> iter = elementList.iterator(); iter.hasNext();) {
				element = (PdfFileBean) iter.next();
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
			logger.error("DB_E016", sql, param, e);
			throw new DBException("DB_E016", e);
		}
		closeConnection(null, stmt, null);
	}

	/**
	 * 创建Pdf表
	 * 
	 * @param namesapce 数据库名称
	 * @throws DBException
	 */
	public boolean createPdftable(String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		boolean success = false;
		// 生成SQL
		String presql = SqlUtil.getSqlbyId("createPdfRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		try {
			success = execute(sql, conn);
		} catch (DBException e) {
			logger.error("DB_E017", sql, e);
			throw new DBException("DB_E017", e);
		}
		commit(conn);
		closeConnection(null, null, conn);
		return success;
	}

	/**
	 * 插入Pdf记录
	 * 
	 * @param beanList Pdf文件数据
	 * @param filepath 文件路径
	 * @param lastmodify 最后修改时间
	 * @param filename 文件名称
	 * @param namespace 数据库 
	 * @throws DBException
	 * @throws LogicException
	 */
	public boolean insertPdfRecord(List<PdfFileBean> beanList, String filepath, long lastmodify,
			String filename, String namesapce) throws LogicException, DBException {
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		// 
		String presql = SqlUtil.getSqlbyId("insertPdfRecord");
		Map<String, String> paramMap = new HashMap<String, String>();
		paramMap.put("namespace", namesapce);
		String sql = SQLParameterUtil.convertSQL(presql, paramMap);
		PdfFileBean element = null;
		try {
			conn.setReadOnly(false);
			for (Iterator<PdfFileBean> iter = beanList.iterator(); iter.hasNext();) {
				element = (PdfFileBean) iter.next();
				element.setFilename(filename);
				element.setLastmodify(lastmodify);
				element.setPath(filepath);
			}
			executePdfUpdateSQL(conn, sql, beanList);
		} catch (Exception e) {
			String param = SQLParameterUtil.getBeanToString(element);
			logger.error("DB_E018", sql, param, e);
			throw new DBException("DB_E018", e);
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
		Connection conn = BaseDao.getConn(namesapce);
		openTransaction(conn);
		Statement st = null;
		try {
			conn.setReadOnly(false);
			st = conn.createStatement();
			String sql = "Load Data InFile " + datapath
					+ " Into Table t_pdf FIELDS TERMINATED BY ','";
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
