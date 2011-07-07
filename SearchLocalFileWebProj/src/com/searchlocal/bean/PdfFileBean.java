package com.searchlocal.bean;

public class PdfFileBean extends BaseFileBean {

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
