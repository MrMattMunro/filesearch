package com.web.searchlocal.entity;

import java.io.Serializable;

public class PageEntity implements Serializable {

	/**
	 * serialVersionUID
	 */
	private static final long serialVersionUID = 1L;

	private int totalRows;

	private int pageSize = 7;

	private int currentPage;

	private int totalPages;

	private int startRow;

	private int endRow;

	/**
	 * @return Returns the endRow.
	 */
	public int getEndRow() {
		endRow = startRow + pageSize;
		if (endRow > totalRows) {
			endRow = totalRows;
		}
		return endRow;
	}

	/**
	 * @param endRow
	 *            The endRow to set.
	 */
	public void setEndRow(int endRow) {
		this.endRow = endRow;
	}


	public PageEntity() {
	}


	public PageEntity(int _totalRows) {
		totalRows = _totalRows;
		totalPages = totalRows / pageSize;
		int mod = totalRows % pageSize;
		if (mod > 0) {
			totalPages++;
		}
		currentPage = 1;
		startRow = 0;

	}


	public int getCurrentPage() {
		return currentPage;
	}

	public void setCurrentPage(int theCurrentPage) {
		currentPage = theCurrentPage;
	}

	public int getPageSize() {
		return pageSize;
	}


	public void setPageSize(int thePageSize) {
		pageSize = thePageSize;
	}

	/**
	 */
	public int getStartRow() {
		return startRow;
	}


	public void setStartRow(int theStartRow) {
		startRow = theStartRow;
	}


	public int getTotalPages() {
		return totalPages;
	}


	public void setTotalPages(int theTotalPages) {
		totalPages = theTotalPages;
	}

	
	public int getTotalRows() {
		return totalRows;
	}


	public void setTotalRows(int theTotalRows) {
		totalRows = theTotalRows;
	}


	public void first() {
		currentPage = 1;
		startRow = 0;
	}


	public void previous() {
		if (currentPage == 1) {
			return;
		}
		currentPage--;
		startRow = (currentPage - 1) * pageSize;
	}


	public void next() {
		if (currentPage < totalPages) {
			currentPage++;
		}
		startRow = (currentPage - 1) * pageSize;
	}


	public void last() {
		currentPage = totalPages;
		startRow = (currentPage - 1) * pageSize;
	}


	public void toThePage(int thepage) {
		if (thepage <= totalPages) {
			currentPage = thepage;
			startRow = (thepage - 1) * pageSize;
		}
		if (thepage > totalPages) {
			this.last();
		}
		if (thepage <= 0) {
			this.first();
		}
	}


	public void refresh(int _currentPage) {
		currentPage = _currentPage;
		if (currentPage > totalPages) {
			last();
		}
	}
}
