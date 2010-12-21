package com.searchlocal.bean;

/**
 * Word文档
 * 
 * <p>Title: Word文档</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class WordFileBean extends BaseFileBean {

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
