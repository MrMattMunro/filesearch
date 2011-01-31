/**
 * $RCSfile: ResultBean.java
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
 * 搜索结果Bean,用于VC的快速查找界面显示用
 * 
 * <p>Title: 搜索结果Bean</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ResultBean extends BaseFileBean {

	/** Id */
	private String id;
	
	/** 对象文档类型 */
	private String fileType;

	/** 文件路径 */
	private String filePath;
	
	/** 描述 */
	private String desp;

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
	 * 取得filePath
	 * 
	 * @return String filePath 
	 */
	public String getFilePath() {
		return filePath;
	}

	/**
	 * 设定filePath 
	 * 
	 * @param String filePath 
	 */
	public void setFilePath(String filePath) {
		this.filePath = filePath;
	}

	/**
	 * 取得desp
	 * 
	 * @return String desp 
	 */
	public String getDesp() {
		return desp;
	}

	/**
	 * 设定desp 
	 * 
	 * @param String desp 
	 */
	public void setDesp(String desp) {
		this.desp = desp;
	}
	
}
