#include "output.h"
#include <QTime>
#include <QMenu>

Output::Output(QWidget *pParent)
    : QPlainTextEdit( pParent )
{

}

void Output::appendMessage(const QString &pText)
{
    appendHtml( QString("<font color=\"#000000\">%1 %2</font>").arg( QTime::currentTime().toString("hh:mm:ss") ).arg(pText) );
}

void Output::appendWarningMessage(const QString &pText)
{
    appendHtml( QString("<font color=\"#808000\">%1 %2</font>").arg( QTime::currentTime().toString("hh:mm:ss") ).arg(pText) );
}

void Output::appendErrorMessage(const QString &pText)
{
    appendHtml( QString("<font color=\"#b20808\">%1 %2</font>").arg( QTime::currentTime().toString("hh:mm:ss") ).arg(pText) );
}

void Output::appendUserMessage(const QString &pText)
{
    appendHtml( QString("<font color=\"#0000aa\">%1 %2</font>").arg( QTime::currentTime().toString("hh:mm:ss") ).arg(pText) );
}

void Output::appendUserErrorMessage(const QString &pText)
{
    appendHtml( QString("<font color=\"#b20808\">%1 %2</font>").arg( QTime::currentTime().toString("hh:mm:ss") ).arg(pText) );
}

void Output::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu();

    QAction* copyAction = menu->addAction( tr("&Copy"), this, SLOT(copy()), QKeySequence::Copy );
    copyAction->setEnabled( textCursor().hasSelection() );

    menu->addSeparator();

    QAction* selectAllAction = menu->addAction( tr("Select All"), this, SLOT(selectAll()), QKeySequence::SelectAll );
    selectAllAction->setEnabled( !document()->isEmpty() );

    menu->addSeparator();

    QAction* clearAction = menu->addAction( tr("Clear"), this, SLOT(clear()) );
    clearAction->setEnabled( !document()->isEmpty() );

    menu->exec(event->globalPos());
    delete menu;
}
