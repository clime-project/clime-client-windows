
CC = gcc
CXX = g++
CFLAGS = $(BASICOPTS) $(MOREOPTS) $(DEFINES)
CPPFLAGS = $(BASICOPTS) $(DEFINES)

LIBS=-luser32 -lgdi32 -mwindows
#LIBS=-luser32 -lgdi32 -lSJDAPI libhook.a -Wl,--enable-auto-import

OBJS = $(TARGETDIR)/Types.o           \
       $(TARGETDIR)/DictionaryInfo.o  \
       $(TARGETDIR)/SearchResult.o    \
       $(TARGETDIR)/RequestID.o       \
       $(TARGETDIR)/ResponseID.o      \
       $(TARGETDIR)/SocketClient.o    \
       $(TARGETDIR)/EngineProxy.o     \
       $(TARGETDIR)/ReadBuffer.o      \
       $(TARGETDIR)/WriteBuffer.o     \
       $(TARGETDIR)/Resource.o        \
       $(TARGETDIR)/IniFile.o         \
       $(TARGETDIR)/Colors.o          \
       $(TARGETDIR)/ColorTheme.o      \
       $(TARGETDIR)/SendMethod.o      \
       $(TARGETDIR)/Config.o          \
       $(TARGETDIR)/Candidates.o      \
       $(TARGETDIR)/WindowMover.o     \
       $(TARGETDIR)/Box.o             \
       $(TARGETDIR)/TextBox.o         \
       $(TARGETDIR)/ListBox.o         \
       $(TARGETDIR)/InputBox.o        \
       $(TARGETDIR)/HotKeys.o         \
       $(TARGETDIR)/MainWindow.o      \
       $(TARGETDIR)/WinAPI.o          \
       $(TARGETDIR)/UTF16.o           \
       $(TARGETDIR)/main.o


.SUFFIXES: .c .cxx .o .hxx .h .rc

dummy:
	@echo xxx

make-target: $(TARGETDIR) $(TARGETDIR)/$(TARGET)

deploy-target:
	strip $(TARGETDIR)/$(TARGET)
	cp -p $(TARGETDIR)/$(TARGET)  $(DEPLOYDIR)/$(TARGET)

package-target:
	strip $(TARGETDIR)/$(TARGET)
	cp -p $(TARGETDIR)/$(TARGET)  $(PACKAGEDIR)/$(TARGET)

$(TARGETDIR)/$(TARGET): $(TARGETDIR) $(OBJS)
	$(LINK.cc) $(OBJS) $(OPTLIBS) -o $@ $(LIBS)

# (必要な場合) ターゲットディレクトリを作成
$(TARGETDIR):
	mkdir -p $(TARGETDIR)

$(TARGETDIR)/%.o: %.rc
	windres -i $< -o $@

# ソースファイルを .o ファイルにコンパイル
$(TARGETDIR)/%.o: %.cxx
	$(COMPILE.cc) -std=c++11 -Wall -Wextra -pedantic $(OPTINC) $< -o $@

clean:
	rm -f $(TARGETDIR)/*.o
	rm -f $(TARGETDIR)/$(TARGET)
	rm -f *~



# DO NOT DELETE

