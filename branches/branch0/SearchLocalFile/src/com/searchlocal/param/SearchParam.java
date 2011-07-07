/**
 * $RCSfile: MessageParam.java
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
 * 显示消息对应的Message
 * 
 * <p>Title: 显示消息对应的Message</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class SearchParam {

	/** 关键字 */
	private String keyWord;

	/** 索引保存路径 */
	private String indexPath;

	/** 开始行 */
	private int startRow;

	/** 结束行 */
	private int endRow;

	/**
	 * 取得keyWord
	 * 
	 * @return String keyWord 
	 */
	public String getKeyWord() {
		return keyWord;
	}

	/**
	 * 设定keyWord 
	 * 
	 * @param String keyWord 
	 */
	public void setKeyWord(String keyWord) {
		this.keyWord = keyWord;
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
	 * 取得startRow
	 * 
	 * @return int startRow 
	 */
	public int getStartRow() {
		return startRow;
	}

	/**
	 * 设定startRow 
	 * 
	 * @param int startRow 
	 */
	public void setStartRow(int startRow) {
		this.startRow = startRow;
	}

	/**
	 * 取得endRow
	 * 
	 * @return int endRow 
	 */
	public int getEndRow() {
		return endRow;
	}

	/**
	 * 设定endRow 
	 * 
	 * @param int endRow 
	 */
	public void setEndRow(int endRow) {
		this.endRow = endRow;
	}
	
}
