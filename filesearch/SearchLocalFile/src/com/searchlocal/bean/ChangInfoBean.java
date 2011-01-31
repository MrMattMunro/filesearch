/**
 * $RCSfile: ChangInfoBean.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.bean;

/**
 * 目录监控中变化的文件
 * 
 * <p>Title: 变化的文件</p>
 * <p>Description: 目录中变化的文件</p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ChangInfoBean {

	/** 文件名 */
	private String id;

	/** 文件路径 */
	private String path;

	/** 操作标志 */
	private String operflg;

	/** 是否已操作 */
	private String hasoper;

	/** 最后修改时间 */
	private long lastmodify;

	/**
	 * 取得id
	 * 
	 * @return String id 
	 */
	public String getId() {
		return id;
	}

	/**
	 * 设定id 
	 * 
	 * @param String id 
	 */
	public void setId(String id) {
		this.id = id;
	}

	/**
	 * 取得path
	 * 
	 * @return String path 
	 */
	public String getPath() {
		return path;
	}

	/**
	 * 设定path 
	 * 
	 * @param String path 
	 */
	public void setPath(String path) {
		this.path = path;
	}

	/**
	 * 取得operflg
	 * 
	 * @return String operflg 
	 */
	public String getOperflg() {
		return operflg;
	}

	/**
	 * 设定operflg 
	 * 
	 * @param String operflg 
	 */
	public void setOperflg(String operflg) {
		this.operflg = operflg;
	}

	/**
	 * 取得hasoper
	 * 
	 * @return String hasoper 
	 */
	public String getHasoper() {
		return hasoper;
	}

	/**
	 * 设定hasoper 
	 * 
	 * @param String hasoper 
	 */
	public void setHasoper(String hasoper) {
		this.hasoper = hasoper;
	}

	/**
	 * 取得lastmodify
	 * 
	 * @return long lastmodify 
	 */
	public long getLastmodify() {
		return lastmodify;
	}

	/**
	 * 设定lastmodify 
	 * 
	 * @param long lastmodify 
	 */
	public void setLastmodify(long lastmodify) {
		this.lastmodify = lastmodify;
	}

}
