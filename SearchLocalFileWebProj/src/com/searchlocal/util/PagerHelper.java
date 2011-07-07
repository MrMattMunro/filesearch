package com.searchlocal.util;

import com.searchlocal.constants.Constant;
import com.searchlocal.entity.PageEntity;

public class PagerHelper {

	public static PageEntity getPager(String currentPage, String goPage,
			String pagerMethod, int totalRows) {

		PageEntity pager = new PageEntity(totalRows);

		if (currentPage != null) {
			pager.refresh(Integer.parseInt(currentPage));
		}

		if (goPage != null && pagerMethod == null) {
			pager.toThePage(Integer.parseInt(goPage));
		}

		if (pagerMethod != null) {
			if (Constant.PageAction.TO_PREVIOUS.equals(pagerMethod)) {
				pager.previous();
			} else if (Constant.PageAction.TO_NEXT.equals(pagerMethod)) {
				pager.next();
			}
		}
		return pager;
	}
}
