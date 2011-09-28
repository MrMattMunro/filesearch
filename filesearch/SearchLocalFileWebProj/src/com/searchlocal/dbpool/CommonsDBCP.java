package com.web.searchlocal.dbpool;

import java.sql.Connection;
import java.sql.SQLException;

import org.apache.commons.dbcp.BasicDataSource;
import org.apache.commons.dbcp.ConnectionFactory;
import org.apache.commons.dbcp.DataSourceConnectionFactory;

public class CommonsDBCP {

	private static ConnectionFactory fac = null;

	public CommonsDBCP(ConnectionParam param) {
		
		BasicDataSource bds = new BasicDataSource();
		bds.setDriverClassName(param.getDriver()); // 
		bds.setUrl(param.getUrl()); // 
		bds.setUsername(param.getUser()); //
		bds.setPassword(param.getPassword()); //
		bds.setMaxActive(1000);
		bds.setInitialSize(500); // ?
		bds.setMaxIdle(40); // ?
		bds.setMaxWait(1000 * 120); //

		fac = new DataSourceConnectionFactory(bds); //
	}

	/**
	 * @param args
	 * @throws SQLException
	 */
	public Connection getConn() throws SQLException {
		Connection conn = fac.createConnection(); // ?
		return conn;
	}
}
