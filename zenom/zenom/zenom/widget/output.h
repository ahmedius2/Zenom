#ifndef OUTPUT_H
#define OUTPUT_H

#include <QPlainTextEdit>

class Output : public QPlainTextEdit
{
    Q_OBJECT

public:
    Output(QWidget *pParent = 0);

public slots:
    void appendMessage( const QString& pText );

    void appendWarningMessage( const QString& pText );

    void appendErrorMessage( const QString& pText );

    void appendUserMessage( const QString& pText );

    void appendUserErrorMessage( const QString& pText );

protected:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // OUTPUT_H
