/**
 * $RCSfile: FileParam.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.param;

/**
 * 文件列表
 * 
 * <p>Title: 文件列表</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileParam {

	/**  文件路径 */
	private String path;

	/**  最后修改时间 */
	private Long lastModify;

	/**  是否存在错误 */
	private String error;

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
	 * 取得lastModify
	 * 
	 * @return Long lastModify 
	 */
	public Long getLastModify() {
		return lastModify;
	}

	/**
	 * 设定lastModify 
	 * 
	 * @param Long lastModify 
	 */
	public void setLastModify(Long lastModify) {
		this.lastModify = lastModify;
	}

	/**
	 * 取得error
	 * 
	 * @return String error 
	 */
	public String getError() {
		return error;
	}

	/**
	 * 设定error 
	 * 
	 * @param String error 
	 */
	public void setError(String error) {
		this.error = error;
	}

}
