package com.searchlocal.menu;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Timer;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.UnsupportedLookAndFeelException;

import snoozesoft.systray4j.SubMenu;
import snoozesoft.systray4j.SysTrayMenu;
import snoozesoft.systray4j.SysTrayMenuEvent;
import snoozesoft.systray4j.SysTrayMenuIcon;
import snoozesoft.systray4j.SysTrayMenuItem;
import snoozesoft.systray4j.SysTrayMenuListener;

import com.searchlocal.constants.Constant;
import com.searchlocal.menu.en.ENAboutFrame;
import com.searchlocal.menu.en.ENAddDicFrame;
import com.searchlocal.menu.en.ENCreateNewFrame;
import com.searchlocal.menu.en.ENModifyFrame;
import com.searchlocal.menu.en.ENOptionSetFrame;
import com.searchlocal.menu.jp.JPAboutFrame;
import com.searchlocal.menu.jp.JPAddDicFrame;
import com.searchlocal.menu.jp.JPCreateNewFrame;
import com.searchlocal.menu.jp.JPModifyFrame;
import com.searchlocal.menu.jp.JPOptionSetFrame;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.thread.concurrent.ConcurrentFileCore;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.CourseUtil;
import com.searchlocal.util.FileOpenerUtil;
import com.searchlocal.util.FileUtil;
import com.searchlocal.util.MenuMessageUtil;
import com.searchlocal.util.RegistTableUtil;
import com.searchlocal.util.XMLConfig;

public class  SearchlocalApp implements ActionListener, SysTrayMenuListener {

	private static String url = "http://localhost:6666/slfile/load";

	private static SysTrayMenu menu;

	private static JFrame frame;

	private static MenuMessageUtil msg = new MenuMessageUtil();

	private static List searches;

	private static SysTrayMenuIcon icos;

	private static SubMenu createdsearch;

	private static int currentIndexIcon;

	//图标列表，两个图标是为了图标切换（闪烁）
	// create icons
	static final SysTrayMenuIcon[] searchicos = {
			new SysTrayMenuIcon("icos/search"),
			new SysTrayMenuIcon("icos/1"),
			new SysTrayMenuIcon("icos/2"),
			new SysTrayMenuIcon("icos/3"),
			new SysTrayMenuIcon("icos/4")};

	private static final String[] toolTips = {
			msg.getMsgbyId(Constant.searchapp_localsearch),
			msg.getMsgbyId(Constant.searchapp_creatingindex),
			msg.getMsgbyId(Constant.searchapp_updatingindex),
			msg.getMsgbyId(Constant.searchapp_deletingindex)
	};

    static class ChangeIcoTask extends java.util.TimerTask {
		public void run() {
			currentIndexIcon = currentIndexIcon + 1;
			if (currentIndexIcon == 5) {
				currentIndexIcon = 1;
			}
			menu.setIcon(searchicos[currentIndexIcon]);
		}
	} 
	   
    private static Timer timer = null;
	private static void changeIcos() {
		timer = new Timer();
		timer.schedule(new ChangeIcoTask(), 100, 500);
	}
	
	public static void startWork(int toolTipsIndex) {
		changeIcos();
	    changeToolTips(toolTipsIndex);
	}
	
	public static void completeWork() {
	    if(timer != null){
	    	timer.cancel();
	    }
	    changeToolTips(Constant.ToolTipsClassify.TOOLTIPS_LOCALSEARCH);
	    menu.setIcon(searchicos[0]);
	}

	private static void changeToolTips(int toolTipsIndex) {
		menu.setToolTip(toolTips[toolTipsIndex]);
	}

	public SearchlocalApp() {

		frame = new JFrame(msg.getMsgbyId(Constant.searchapp_title));

		frame.setSize(400, 300);
		icos = searchicos[0];

		menu = new SysTrayMenu(icos, toolTips[0]);
		createMenu();

		new ConstantExeFileUtil();

		icos.addSysTrayMenuListener(this);
		//把图标加入监听，这样就可以有左键监听了
		searchicos[0].addSysTrayMenuListener(this);
		searchicos[1].addSysTrayMenuListener(this);
		
		// 开始复制jcom.dll到JDK目录
		copydll();

		ConcurrentFileCore.listen();
	}

	/**
	 * 将jcom.dll复制到Jre的Bin目录下
	 */
	static void copydll() {
		// 取得目的文件
		String jdkpath = RegistTableUtil.getJavaInstallRoot();
		jdkpath = jdkpath + File.separator+ "bin";
		String jcomfile = jdkpath + File.separator+ Constant.jcomdll;
	
		File file = new File(jcomfile);
		// 文件不存在的情况下
		if(!file.exists()){
			// 取得原文件
			String orgjcomfile =  Constant.lib_path + Constant.jcomdll;
			System.out.println("file:::" + file.getAbsolutePath());
		    System.out.println("orgjcomfile:::" + orgjcomfile);
			FileUtil.copyFile(new File(orgjcomfile), file);
		}
	}
	
	/**
	 * 生成菜单
	 */
	void createMenu() {
		// 菜单列表
		Vector<SysTrayMenuItem> items = new Vector<SysTrayMenuItem>();

		XMLConfig xmlconfig = new XMLConfig();
		searches = xmlconfig.getEntityList();
		for (Iterator iter = searches.iterator(); iter.hasNext();) {
			CreateNewParam element = (CreateNewParam) iter.next();
			SysTrayMenuItem item = new SysTrayMenuItem(element.getSearchname(),
					element.getSearchname());
			item.addSysTrayMenuListener(this);
			items.add(item);
		}

		// 新建
		createdsearch = new SubMenu(
				msg.getMsgbyId(Constant.menu_createdsearch), items);
		SysTrayMenuItem creatsearch = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_createsearch),
				Constant.MenuName.CREATESEARCH);
		creatsearch.addSysTrayMenuListener(this);
		SysTrayMenuItem option = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_option), Constant.MenuName.OPTION);
		option.addSysTrayMenuListener(this);

		// 自定义词典
		SysTrayMenuItem adddic = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_customdic), Constant.MenuName.ADDDIC);
		adddic.addSysTrayMenuListener(this);

		// 关于
		SysTrayMenuItem about = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_about), Constant.MenuName.ABOUT);
		about.addSysTrayMenuListener(this);
		
		// 帮助
		SysTrayMenuItem help = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_help), Constant.MenuName.HELP);
		help.addSysTrayMenuListener(this);

		// 退出
		SysTrayMenuItem exit = new SysTrayMenuItem(msg
				.getMsgbyId(Constant.menu_exit), Constant.MenuName.EXIT);
		exit.addSysTrayMenuListener(this);

		// 加入Menu
		menu.addItem(exit);
		menu.addItem(help);
		menu.addItem(about);
		menu.addSeparator();
		menu.addItem(option);
		menu.addItem(adddic);
		menu.addItem(createdsearch);
		menu.addItem(creatsearch);
	}

	/**
	 * ???ActionListener????????
	 */
	public void actionPerformed(ActionEvent e) {
	}

	/**
	 * ???SysTrayMenuListener??????????????????????
	 */
	public void iconLeftClicked(SysTrayMenuEvent arg0) {

	}

	/**
	 * ???SysTrayMenuListener???????????????????????
	 */
	public void iconLeftDoubleClicked(SysTrayMenuEvent arg0) {
		FileOpenerUtil fileopener = new FileOpenerUtil(null);
		String opener = fileopener.getOpenerbyId("ie");
		try {
			Runtime.getRuntime().exec(opener + " " + url);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Menu的点击事件
	 */
	public void menuItemSelected(SysTrayMenuEvent sme) {
		try {
//			if (!CheckLincese.checkLincese() && !sme.getActionCommand().equals(Constant.MenuName.EXIT)) {
//				String errormsg = msg.getMsgbyId(Constant.errors_lincese);
//				MessageFrame.showmessage(errormsg);
//				return;
//			}
			// 取得当前电脑的区域
			Locale local = Locale.getDefault();
			String languagep = local.getLanguage();
			String language = Constant.LanguageClassify.ENGLISH;
			if ("zh".equals(languagep)) {
				language = Constant.LanguageClassify.CHINESE;
			}
			if ("ja".equals(languagep)) {
				language = Constant.LanguageClassify.JAPANESE;
			}

			for (Iterator iter = searches.iterator(); iter.hasNext();) {
				CreateNewParam element = (CreateNewParam) iter.next();
				if (sme.getActionCommand().equals(element.getSearchname())) {
					if(language.equals(Constant.LanguageClassify.JAPANESE)){
						JPModifyFrame jpmodifyframe = new JPModifyFrame(element);
						jpmodifyframe.showfame();
					}
					if(language.equals(Constant.LanguageClassify.ENGLISH)){
						ENModifyFrame enmodifyframe = new ENModifyFrame(element);
						enmodifyframe.showfame();
					}
					if(language.equals(Constant.LanguageClassify.CHINESE)){
						ModifyFrame modifyframe = new ModifyFrame(element);
						modifyframe.showfame();
					}
				}
			}
			if (sme.getActionCommand().equals(Constant.MenuName.EXIT)) {
				CourseUtil.shutdown();
				System.exit(0);
			} else if (sme.getActionCommand().equals(Constant.MenuName.CREATESEARCH)) {
				if(language.equals(Constant.LanguageClassify.JAPANESE)){
					JPCreateNewFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.ENGLISH)){
					ENCreateNewFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.CHINESE)){
					CreateNewFrame.showframe();
				}
			} else if (sme.getActionCommand().equals(Constant.MenuName.OPTION)) {
				if(language.equals(Constant.LanguageClassify.JAPANESE)){
					JPOptionSetFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.ENGLISH)){
					ENOptionSetFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.CHINESE)){
					OptionSetFrame.showframe();
				}
			} else if (sme.getActionCommand().equals(Constant.MenuName.ADDDIC)) {
				if(language.equals(Constant.LanguageClassify.JAPANESE)){
					JPAddDicFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.ENGLISH)){
					ENAddDicFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.CHINESE)){
					AddDicFrame.showframe();
				}
			} else if (sme.getActionCommand().equals(Constant.MenuName.ABOUT)) {
				if(language.equals(Constant.LanguageClassify.JAPANESE)){
					JPAboutFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.ENGLISH)){
					ENAboutFrame.showframe();
				}
				if(language.equals(Constant.LanguageClassify.CHINESE)){
					AboutFrame.showframe();
				}
			} else if (sme.getActionCommand().equals(Constant.MenuName.HELP)) {
				try {
					ConstantExeFileUtil.readFile();
					String exepath = ConstantExeFileUtil.getOpenerbyId("chm");
					if(language.equals(Constant.LanguageClassify.JAPANESE)){
						String filepath = Constant.datapath + "help//Help_jp.chm";
						//filepath = filepath.substring(1);
						Runtime.getRuntime().exec(exepath + " " + filepath);
					}
					if(language.equals(Constant.LanguageClassify.ENGLISH)){
						String filepath = Constant.datapath + "help//Help_en.chm";
						filepath = filepath.substring(1);
						Runtime.getRuntime().exec(exepath + " " + filepath);
					}
					if(language.equals(Constant.LanguageClassify.CHINESE)){
						String filepath = Constant.datapath + "help//Help_cn.chm";
						filepath = filepath.substring(1);
						Runtime.getRuntime().exec(exepath + " " + filepath);
					}
				} catch (IOException e) {
					// TODO 注意消除资源(关闭I/O等)
					e.printStackTrace();
				}
			}

		} catch (UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		}
	}

	public static void main(String args[]) {
		 new SearchlocalApp();
		// copydll();
	}
}
