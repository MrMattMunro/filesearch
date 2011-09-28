package com.web.searchlocal.bean;

public class ExcelFileBean extends BaseFileBean {

	private String sheetname;

	private int rownb;

	/**
	 * @return Returns the rownb.
	 */
	public int getRownb() {
		return rownb;
	}

	/**
	 * @param rownb
	 *            The rownb to set.
	 */
	public void setRownb(int rownb) {
		this.rownb = rownb;
	}

	/**
	 * @return Returns the sheetname.
	 */
	public String getSheetname() {
		return sheetname;
	}

	/**
	 * @param sheetname
	 *            The sheetname to set.
	 */
	public void setSheetname(String sheetname) {
		this.sheetname = sheetname;
	}

}
