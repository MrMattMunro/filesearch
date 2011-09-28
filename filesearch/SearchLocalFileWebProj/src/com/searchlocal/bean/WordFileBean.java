/**
 * $RCSfile: WordFileBean.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.bean;

/**
 * Word文档
 * 
 * <p>Title: Word文档</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class WordFileBean extends BaseFileBean {
	
	/** 页码 */
	private int page;

	/**
	 * @return Returns the page.
	 */
	public int getPage() {
		return page;
	}

	/**
	 * @param page
	 *            The page to set.
	 */
	public void setPage(int page) {
		this.page = page;
	}

	/** 段落 */
	private int paragraphNo;

	/**
	 * @return Returns the paragraphNo.
	 */
	public int getParagraphNo() {
		return paragraphNo;
	}

	/**
	 * @param paragraphNo
	 *            The paragraphNo to set.
	 */
	public void setParagraphNo(int paragraphNo) {
		this.paragraphNo = paragraphNo;
	}

}
