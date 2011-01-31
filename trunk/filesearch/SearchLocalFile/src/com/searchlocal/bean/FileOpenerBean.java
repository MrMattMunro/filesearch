/**
 * $RCSfile: FileOpenerBean.java
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
 * 打开文件路径信息
 * 
 * <p>Title: 打开文件路径信息</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileOpenerBean extends BaseFileBean {

	/** Id */
	private String id;
	
	/** 对象文档类型 */
	private String fileType;

	/** 打开exe路径 */
	private String exePath;
	
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
	 * 取得fileType
	 * 
	 * @return String fileType 
	 */
	public String getFileType() {
		return fileType;
	}

	/**
	 * 设定fileType 
	 * 
	 * @param String fileType 
	 */
	public void setFileType(String fileType) {
		this.fileType = fileType;
	}

	/**
	 * 取得exePath
	 * 
	 * @return String exePath 
	 */
	public String getExePath() {
		return exePath;
	}

	/**
	 * 设定exePath 
	 * 
	 * @param String exePath 
	 */
	public void setExePath(String exePath) {
		this.exePath = exePath;
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
