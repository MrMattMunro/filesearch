package com.searchlocal.dbpool;

import java.io.Serializable;

public class ConnectionParam implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private String driver; // ?

	private String url; // 

	private String user; // 

	private String password; // ?

	public ConnectionParam(String driver, String url, String user, String password) {
		this.driver = driver;
		this.url = url;
		this.user = user;
		this.password = password;
	}

	public String getDriver() {
		return driver;
	}

	public String getPassword() {
		return password;
	}

	public String getUrl() {
		return url;
	}

	public String getUser() {
		return user;
	}

	public void setDriver(String driver) {
		this.driver = driver;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public void setUser(String user) {
		this.user = user;
	}

	/**
	 * @see java.lang.Object#clone()
	 */
	public Object clone() {
		ConnectionParam param = new ConnectionParam(driver, url, user, password);
		return param;
	}

	/**
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	public boolean equals(Object obj) {
		if (obj instanceof ConnectionParam) {
			ConnectionParam param = (ConnectionParam) obj;
			return ((driver.compareToIgnoreCase(param.getDriver()) == 0)
					&& (url.compareToIgnoreCase(param.getUrl()) == 0)
					&& (user.compareToIgnoreCase(param.getUser()) == 0) && (password
					.compareToIgnoreCase(param.getPassword()) == 0));
		}
		return false;
	}
}
