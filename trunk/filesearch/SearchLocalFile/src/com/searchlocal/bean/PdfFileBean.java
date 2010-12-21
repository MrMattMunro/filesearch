package com.searchlocal.bean;

/**
 * Pdf文件
 * 
 * <p>Title: Pdf文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.com</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class PdfFileBean extends BaseFileBean {

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

	public PdfFileBean() {
		super();
	}

}
