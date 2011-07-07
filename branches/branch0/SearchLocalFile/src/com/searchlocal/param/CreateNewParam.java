/**
 * $RCSfile: CreateNewParam.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.param;

import java.util.List;

/**
 * 创建搜索对象时,数据存储对象
 * 
 * <p>Title: 创建搜索对象时,数据存储对象</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class CreateNewParam {

	/**  搜索名称 */
	private String searchname;

	/**  搜索路径 */
	private String path;

	/** 文档类型 */
	private List<String> selectfiletype;

	/**  索引保存目录 */
	private String indexpath;

	/**
	 * 取得searchname
	 * 
	 * @return String searchname 
	 */
	public String getSearchname() {
		return searchname;
	}

	/**
	 * 设定searchname 
	 * 
	 * @param String searchname 
	 */
	public void setSearchname(String searchname) {
		this.searchname = searchname;
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
	 * 取得selectfiletype
	 * 
	 * @return List selectfiletype 
	 */
	public List<String> getSelectfiletype() {
		return selectfiletype;
	}

	/**
	 * 设定selectfiletype 
	 * 
	 * @param List selectfiletype 
	 */
	public void setSelectfiletype(List<String> selectfiletype) {
		this.selectfiletype = selectfiletype;
	}

	/**
	 * 取得indexpath
	 * 
	 * @return String indexpath 
	 */
	public String getIndexpath() {
		return indexpath;
	}

	/**
	 * 设定indexpath 
	 * 
	 * @param String indexpath 
	 */
	public void setIndexpath(String indexpath) {
		this.indexpath = indexpath;
	}

}
