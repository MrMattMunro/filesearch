/**
 * $RCSfile: SearcherBean.java
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
 * 搜索对象
 * 
 * <p>Title: 同步文件与数据库任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearcherBean {

	/** Id */
	private String id;
	
	/** 文件路径 */
	private String path;

	/** 索引路径 */
	private String indexPath;

	/** 对象文档类型 */
	private String fileType;

	/** 是否已建索引 */
	private String hasCreateIndex;

	/** 是否已更新 */
	private String hasUpdate;

	/** 是否已删除 */
	private String hasDel;

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
	 * 取得indexPath
	 * 
	 * @return String indexPath 
	 */
	public String getIndexPath() {
		return indexPath;
	}

	/**
	 * 设定indexPath 
	 * 
	 * @param String indexPath 
	 */
	public void setIndexPath(String indexPath) {
		this.indexPath = indexPath;
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
	 * 取得hasCreateIndex
	 * 
	 * @return String hasCreateIndex 
	 */
	public String getHasCreateIndex() {
		return hasCreateIndex;
	}

	/**
	 * 设定hasCreateIndex 
	 * 
	 * @param String hasCreateIndex 
	 */
	public void setHasCreateIndex(String hasCreateIndex) {
		this.hasCreateIndex = hasCreateIndex;
	}

	/**
	 * 取得hasUpdate
	 * 
	 * @return String hasUpdate 
	 */
	public String getHasUpdate() {
		return hasUpdate;
	}

	/**
	 * 设定hasUpdate 
	 * 
	 * @param String hasUpdate 
	 */
	public void setHasUpdate(String hasUpdate) {
		this.hasUpdate = hasUpdate;
	}

	/**
	 * 取得hasDel
	 * 
	 * @return String hasDel 
	 */
	public String getHasDel() {
		return hasDel;
	}

	/**
	 * 设定hasDel 
	 * 
	 * @param String hasDel 
	 */
	public void setHasDel(String hasDel) {
		this.hasDel = hasDel;
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
