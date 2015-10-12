#include "texttabedit.h"
#include <QDebug>
TextTabEdit::TextTabEdit(QWidget* parent):QTabWidget(parent)
{

    this->setTabsClosable(true);
    setMinimumHeight(300);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));

}

QString TextTabEdit::addAnotherTab(const QString &filename, const QString &text)
{
    QString name = filename.split("/").last();
    MainTextViewer* current = new MainTextViewer();
    fileNamePath[name] = filename;
    current->setPlainText(text);
    addTab(current,name);
    setCurrentWidget(current);
    return name;
}

QString TextTabEdit::getCurrentText() const
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        return current->toPlainText();
    } else {
        return "";
    }
}

QString TextTabEdit::getCurrentFile() const
{
    int index = currentIndex();
    return fileNamePath[tabText(index)];
}

QString TextTabEdit::getIndexText(int index) const
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->widget(index));
    if(current){
        return current->toPlainText();
    }
}

void TextTabEdit::highLightPatterns(const QStringList &patterns)
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        current->highlightPatterns(patterns);
    }
}

void TextTabEdit::deHighlightPatterns(const QStringList &patterns)
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        current->dehighlightPatterns(patterns);
    }
}


void TextTabEdit::setMatches(const PatternViewMap &m)
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        current->setMatches(m);
    }
}

void TextTabEdit::selectText(int start, int end)
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        current->selectText(start,end);
    }
}

void TextTabEdit::clearSelection()
{
    MainTextViewer* current = static_cast<MainTextViewer*>(this->currentWidget());
    if(current){
        current->clearSelection();
    }
}

void TextTabEdit::closeTab(int index)
{
        MainTextViewer* current = static_cast<MainTextViewer*>(this->widget(index));
        if(current->isModified()){
            QString name = tabText(index);
            TextBasicWidget* par = static_cast<TextBasicWidget*>(this->parent());
            if(par->maybeSave(name,index)){
                this->removeTab(index);
                emit tabWasClosed(index);
            }
        }else{
            this->removeTab(index);
            emit tabWasClosed(index);
        }
}

