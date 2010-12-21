package com.searchlocal.constants;

import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

/**
 * 常量类
 * 
 * <p>Title: 常量类</p>
 * @version 1.0
 */
public class Constant {
	
	public static String datapath = "";
	static {
		 try {
			datapath = Constant.class.getResource("/").toURI().getPath();
			
			//发布的时候注释掉
			datapath = datapath.substring(1);
			datapath = datapath.replaceAll("classes/", "");
		} catch (URISyntaxException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		}
	}
	



	// #------------------------------------------------------------------
	// #------------------------------------------------------------------
	public static String label_dicfilename = "label.dicfilename";
	
	public static String label_dic_note_r1 = "label.labeldicnote_r1";
	
	public static String label_dic_note_r2 = "label.labeldicnote_r2";
	
	public static String label_dic_note_r3 = "label.labeldicnote_r3";
	
	public static String label_searchname = "label.searchname";

	public static String label_searchdir = "label.searchdir";

	public static String label_indexdir = "label.indexdir";

	public static String label_doc = "label.doc";

	public static String label_contact = "label.contact";

	public static String label_homepage = "label.homepage";

	public static String label_setopenersoft = "label.setopenersoft";

	public static String label_ie = "label.ie";

	public static String label_word = "label.word";

	public static String label_excel = "label.excel";

	public static String label_ppt = "label.ppt";

	public static String label_pdf = "label.pdf";

	public static String label_txt = "label.txt";
	
	public static String label_keyword = "label.keyword";

	// #------------------------------------------------------------------
	// #-----------------------buttons------------------------------------
	// #------------------------------------------------------------------
	public static String button_select = "button.select";

	public static String button_confirm = "button.confirm";

	public static String button_cancel = "button.cancel";

	public static String button_delete = "button.delete";

	public static String button_close = "button.close";
	
	public static String button_search = "button.search";
	
	public static String button_viedic = "button.viewdic";

	// #------------------------------------------------------------------
	// #-----------------------frame title--------------------------------
	// #------------------------------------------------------------------
	public static String title_createnew = "title.createnew";

	public static String title_aboutsoft = "title.aboutsoft";

	public static String title_modifysearch = "title.modifysearch";

	public static String title_setopenersoft = "title.setopenersoft";

	public static String title_adddic = "title.adddic";
	
	public static String title_viewdic = "title.viewdic";
	
	public static String file_chooser_selectdicpath = "file.chooser.selectdicpath";
	
	public static String dialog_title_setopenersoft = "dialog.title.setopenersoft";

	public static String file_filter_description = "file.filter.description";

	public static String dialog_title_selectpath = "dialog.title.selectpath";

	public static String dialog_title_selectindexpath = "dialog.title.selectindexpath";

	public static String file_chooser_setsearchpath = "file.chooser.setsearchpath";

	public static String file_chooser_setindexpath = "file.chooser.setindexpath";

	// #------------------------------------------------------------------
	// #-----------------------searchApp menu-----------------------------
	// #------------------------------------------------------------------
	public static String searchapp_title = "searchapp.title";

	public static String searchapp_localsearch = "searchapp.localsearch";
	
	public static String searchapp_creatingindex = "searchapp.creatingindex";
	
	public static String searchapp_updatingindex = "searchapp.updatingindex";
	
	public static String searchapp_deletingindex = "searchapp.deletingindex";

	public static String menu_createdsearch = "menu.createdsearch";

	public static String menu_createsearch = "menu.createsearch";

	public static String menu_customdic = "menu.customdic";
	
	public static String menu_option = "menu.option";

	public static String menu_about = "menu.about";
	
	public static String menu_help = "menu.help";

	public static String menu_exit = "menu.exit";

	// #------------------------------------------------------------------
	// #-----------------------checkobx-----------------------------
	// #------------------------------------------------------------------
	public static String checkbox_iscoverdic = "checkbox.iscoverdic";
	
	// #------------------------------------------------------------------
	// #-----------------------messagessearch-----------------------------
	// #------------------------------------------------------------------
	public static String message_search = "message.search";

	// #------------------------------------------------------------------
	// #--- frame error --------------------------------------------------
	// #------------------------------------------------------------------
	public static String errors_outofversion = "errors.outofversion";

	public static String errors_hasrepeat = "errors.hasrepeat";

	public static String errors_confirmdelete = "errors.confirmdelete";

	public static String errors_confirmimportfile = "errors.confirmimportfile";

	public static String errors_notnull = "errors.notnull";

	public static String errors_hascharacter = "errors.hascharacter";

	public static String errors_isallnums = "errors.isallnums";
	
	public static String errors_isnotdicfile = "errors.isnotdicfile";
	
	public static String errors_dicnotexisted = "errors.dicnotexisted";
	
	public static String errors_lincese = "errors.lincese";
	
	// #------------------------------------------------------------------
	// #--- frame info --------------------------------------------------
	// #------------------------------------------------------------------
	public static String info_nodic = "info.nodic";
	
	public static String info_completeindex = "info.completeindex";
	
	public static String info_updatedindex = "info.updatedindex";
	
	public static String info_deletedindex = "info.deletedindex";
	
	public static String info_currentedindex = "info.currentedindex";

	// #------------------------------------------------------------------
	// #--- about frame content ----------------------------------------
	// #------------------------------------------------------------------
	public static String about_frame_r1 = "about.frame.r1";

	public static String about_frame_r2 = "about.frame.r2";

	public static String about_frame_r3 = "about.frame.r3";

	public static String about_frame_r4 = "about.frame.r4";

	public static String about_frame_r5 = "about.frame.r5";

	public static String about_frame_r6 = "about.frame.r6";

	public static String about_frame_r7 = "about.frame.r7";

	public static String about_frame_r8 = "about.frame.r8";
	
	// #------------------------------------------------------------------
	// #--- 配置路径-------------------------------------------------------
	// #------------------------------------------------------------------
    // public static String path = "tomcat\\webapps\\slfile\\WEB-INF\\classes\\";
    
    public static String lib_path = "tomcat\\webapps\\slfile\\WEB-INF\\lib\\";

	public static String suffixname = ".csv";
	
	public static String jcomdll = "jcom.dll";

    public static String path = "src\\";

    public static String dicpath = "dic\\";
    
    public static String filedatapath = "data/file";
    
    public static String worddatapath = "data/word";
    
    public static String exceldatapath = "data/excel";
    
    public static String pptdatapath = "data/ppt";
    
    public static String pdfdatapath = "data/pdf";
    
    public static String txtdatapath = "data/txt";
    
    public static String htmldatapath = "data/html";
    
    public static String chmdatapath = "data/chm";
    
    public static String diccompilepath = "dic\\.compiled";

	public static String confpath = "tomcat\\webapps\\slfile\\WEB-INF\\conf\\";

	// public static String confpath = "conf\\";

	public static String icospath = "icos/search";
	
	public static String titleicopath = "icos//titleico.jpg";
	
	public static String licencepath = "licence.dat";
	
	// #------------------------------------------------------------------
	// #--- 语言相关配置----------------------------------------------------
	// #------------------------------------------------------------------
	public static String LANGUAGE = "language";

	public static String LANGUAGE_RS = path + "com\\searchlocal\\properties\\language.properties";

	public static String CHINESE_RS = path
			+ "com\\searchlocal\\properties\\ApplicationResources_cn.properties";

	public static String ENGLISH_RS = path
			+ "com\\searchlocal\\properties\\ApplicationResources_en.properties";

	public static String JPANESE_RS = path
			+ "com\\searchlocal\\properties\\ApplicationResources_jp.properties";
	
	public static final String HAS_ERROR = "1";

	public static final String NO_ERROR = "0";

	// #------------------------------------------------------------------
	// #--- 数据库相关配置参数-----------------------------------------------
	// #------------------------------------------------------------------
	public static class DBConstansInfo {

		/** DATABASE_CLASS_FOR_NAME */
		public final static String DATABASE_CLASS_FOR_NAME = "driverClassName";

		/** DATABASE_URL */
		public final static String DATABASE_URL = "url";

		/** DATABASE_USER */
		public final static String DATABASE_USER = "username";

		/** DATABASE_PASSWORD */
		public final static String DATABASE_PASSWORD = "password";

		protected DBConstansInfo() {
		}
	}

	// #------------------------------------------------------------------
	// #--- 后缀名文件分类--------------------------------------------------
	// #------------------------------------------------------------------
	public static class FileClassify {

		public static final String XLS = ".xls";
		
		public static final String XLS2007 = ".xlsx";

		public static final String DOC = ".doc";
		
		public static final String DOC2007 = ".docx";

		public static final String PDF = ".pdf";

		public static final String PPT = ".ppt";
		
		public static final String PPT2007 = ".pptx";

		public static final String TXT = ".txt";

		public static final String CHM = ".chm";

		public static final String HTM = ".HTM";

		public static final String HTML = ".HTML";

		protected FileClassify() {
		}

		public static boolean isHtmlcontain(String suffixName) {
			List<String> allType = new ArrayList<String>();
			allType.add(HTM);
			allType.add(HTML);
			allType.add(HTML.toLowerCase());
			allType.add(HTM.toLowerCase());
			return allType.contains(suffixName);
		}
		
		public static boolean is2007Doccontain(String suffixName) {
			List<String> allType = new ArrayList<String>();
			allType.add(XLS2007);
			allType.add(DOC2007);
			allType.add(PPT2007);
			allType.add(XLS2007.toUpperCase());
			allType.add(DOC2007.toUpperCase());
			allType.add(PPT2007.toUpperCase());
			return allType.contains(suffixName);
		}
	}

	// #------------------------------------------------------------------
	// #--- 代码文件分类----------------------------------------------------
	// #------------------------------------------------------------------
	public static class SrcClassify {

		public static final String JAVA = ".java";

		public static final String C = ".h";

		public static final String JAVASCRIPT = ".js";

		public static final String RUBY = ".rb";

		public static final String ASPX = ".aspx";

		public static final String ASP = ".asp";

		public static final String JSP = ".jsp";

		public static final String PHP = ".php";

		public static final String XML = ".xml";

		public static final String PROPERTY = ".properities";

		public static final String TXT = ".txt";

		protected SrcClassify() {
		}

		public static boolean iscontain(String suffixName) {
			List<String> allType = new ArrayList<String>();
			allType.add(JAVA);
			allType.add(C);
			allType.add(JAVASCRIPT);
			allType.add(RUBY);
			allType.add(ASPX);
			allType.add(ASP);
			allType.add(JSP);
			allType.add(PHP);
			allType.add(PROPERTY);
			allType.add(TXT);
			return allType.contains(suffixName);
		}
	}

	public static class DbErrClassify {

		public static final String DB_E001 = "DB_E001";

		public static final String DB_E002 = "DB_E002";

		public static final String DB_E003 = "DB_E002";

		public static final String DB_E004 = "DB_E004";

		public static final String DB_E005 = "DB_E005";

		public static final String DB_E006 = "DB_E006";

		protected DbErrClassify() {
		}
	}

	public static class ToolTipsClassify {

		public static final int TOOLTIPS_LOCALSEARCH = 0;

		public static final int TOOLTIPS_CREATINGINDEX = 1;

		public static final int TOOLTIPS_UPDATINGINDEX = 2;

		public static final int TOOLTIPS_DELETINGINDEX = 3;

		protected ToolTipsClassify() {
		}
	}
	

	public static class LogicErrClassify {

		public static final String LG_E001 = "LG_E001";

		public static final String LG_E002 = "LG_E002";

		public static final String LG_E003 = "LG_E002";

		public static final String LG_E004 = "LG_E004";

		public static final String LG_E005 = "LG_E005";

		public static final String LG_E006 = "LG_E006";

		protected LogicErrClassify() {
		}
	}

	public static class LanguageClassify {

		public static final String ENGLISH = "english";

		public static final String CHINESE = "chinese";

		public static final String JAPANESE = "japanese";

		protected LanguageClassify() {
		}
	}

	public static class FileNameClassify {

		public static final String EXCEL = "excel";

		public static final String WORD = "word";

		public static final String PDF = "pdf";

		public static final String PPT = "ppt";

		public static final String HTML = "html";

		public static final String TXT = "txt";

		public static final String CHM = "chm";

		protected FileNameClassify() {
		}
	}

	public static class MenuName {

		public static final String CREATESEARCH = "createsearch";

		public static final String OPTION = "option";
		
		public static final String ADDDIC = "adddic";

		public static final String ABOUT = "about";
		
		public static final String HELP = "help";

		public static final String EXIT = "exit";

		protected MenuName() {
		}
	}
}