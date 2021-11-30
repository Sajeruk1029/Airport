#include "NetworkAPIRequester.h"

NetworkAPIRequester::NetworkAPIRequester(QString Url) : networkAccessManager(new QNetworkAccessManager(this)), url(Url), error(0){ networkAccessManager->setTransferTimeout(180000); }
NetworkAPIRequester::~NetworkAPIRequester(){ if(networkAccessManager){ delete networkAccessManager; } }

void NetworkAPIRequester::getAllAccounts(const std::function<void(QList<Accounts>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    { 
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Accounts> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Accounts(jsonObject["Id"].toInt(), jsonObject["Login"].toString(), jsonObject["Password"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAccounts(const std::function<void(QList<Accounts>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Accounts> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Accounts(jsonObject["Id"].toInt(), jsonObject["Login"].toString(), jsonObject["Password"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAccounts(const std::function<void(QList<Accounts>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Accounts> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Accounts(jsonObject["Id"].toInt(), jsonObject["Login"].toString(), jsonObject["Password"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAccounts(const std::function<void (Accounts)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Login", accounts.getLogin());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Accounts accounts(0, "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    accounts.setId(jsonObject["Id"].toInt());
                    accounts.setLogin(jsonObject["Login"].toString());
                    accounts.setPassword(jsonObject["Password"].toString());
                    accounts.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(accounts);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setAccounts(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts oldAccounts, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldAccounts.getId()));
    query.addQueryItem("Login", accounts.getLogin());
    query.addQueryItem("Password", accounts.getPassword());
    query.addQueryItem("IsDeleted", QString::number(accounts.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteAccounts(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(accounts.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverAccounts(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(accounts.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterAccounts(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(accounts.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addAccounts(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Accounts accounts)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Accounts/AccountsSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Login", accounts.getLogin());
    query.addQueryItem("Password", accounts.getPassword());
    query.addQueryItem("IsDeleted", QString::number(accounts.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Acccounts

void NetworkAPIRequester::getAllAirCompany(const std::function<void(QList<AirCompany>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompany> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompany(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompany(const std::function<void(QList<AirCompany>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompany> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompany(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompany(const std::function<void(QList<AirCompany>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompany> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompany(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirCompany(const std::function<void (AirCompany)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanySearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompany.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        AirCompany airCompany(0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airCompany.setId(jsonObject["Id"].toInt());
                    airCompany.setName(jsonObject["Name"].toString());
                    airCompany.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(airCompany);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setAirCompany(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany oldAirCompany, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldAirCompany.getId()));
    query.addQueryItem("Name", airCompany.getName());
    query.addQueryItem("IsDeleted", QString::number(airCompany.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteAirCompany(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompany.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverAirCompany(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompany.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterAirCompany(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanyLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompany.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addAirCompany(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompany airCompany)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanySender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompany.getName());
    query.addQueryItem("IsDeleted", QString::number(airCompany.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompany

void NetworkAPIRequester::getAllAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplane(jsonObject["Id"].toInt(), jsonObject["IdAirplane"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplane(jsonObject["Id"].toInt(), jsonObject["IdAirplane"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplane(jsonObject["Id"].toInt(), jsonObject["IdAirplane"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setAirCompanyAndAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplane oldAirCompanyAndAirplane, AirCompanyAndAirplane airCompanyAndAirplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldAirCompanyAndAirplane.getId()));
    query.addQueryItem("IdAirCompany", QString::number(airCompanyAndAirplane.getIdAirCompany()));
    query.addQueryItem("IdAirplane", QString::number(airCompanyAndAirplane.getIdAirplane()));
    query.addQueryItem("IsDeleted", QString::number(airCompanyAndAirplane.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteAirCompanyAndAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplane airCompanyAndAirplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndAirplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverAirCompanyAndAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplane airCompanyAndAirplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndAirplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterAirCompanyAndAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplane airCompanyAndAirplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndAirplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addAirCompanyAndAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplane airCompanyAndAirplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplane/AirCompanyAndAirplaneSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("IdAirCompany", QString::number(airCompanyAndAirplane.getIdAirCompany()));
    query.addQueryItem("IdAirplane", QString::number(airCompanyAndAirplane.getIdAirplane()));
    query.addQueryItem("IsDeleted", QString::number(airCompanyAndAirplane.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndAirplane

void NetworkAPIRequester::getAllAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServices(jsonObject["Id"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServices(jsonObject["Id"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServices(jsonObject["Id"].toInt(), jsonObject["IdAirCompany"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setAirCompanyAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServices oldAirCompanyAndServices, AirCompanyAndServices airCompanyAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldAirCompanyAndServices.getId()));
    query.addQueryItem("IdAirCompany", QString::number(airCompanyAndServices.getIdAirCompany()));
    query.addQueryItem("IdAirplane", QString::number(airCompanyAndServices.getIdService()));
    query.addQueryItem("IsDeleted", QString::number(airCompanyAndServices.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteAirCompanyAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServices airCompanyAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverAirCompanyAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServices airCompanyAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterAirCompanyAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServices airCompanyAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airCompanyAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addAirCompanyAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServices airCompanyAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("IdAirCompany", QString::number(airCompanyAndServices.getIdAirCompany()));
    query.addQueryItem("IdService", QString::number(airCompanyAndServices.getIdService()));
    query.addQueryItem("IsDeleted", QString::number(airCompanyAndServices.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndServices

void NetworkAPIRequester::getAllAirplane(const std::function<void(QList<Airplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Airplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Airplane(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["MaxSizeCargo"].toInt(), jsonObject["MaxWeightCargo"].toInt(), jsonObject["MaxSeatPlaces"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirplane(const std::function<void(QList<Airplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Airplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Airplane(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["MaxSizeCargo"].toInt(), jsonObject["MaxWeightCargo"].toInt(), jsonObject["MaxSeatPlaces"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirplane(const std::function<void(QList<Airplane>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Airplane> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Airplane(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["MaxSizeCargo"].toInt(), jsonObject["MaxWeightCargo"].toInt(), jsonObject["MaxSeatPlaces"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirplane(const std::function<void (Airplane)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airplane.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Airplane airplane(0, "", "", 0, 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airplane.setId(jsonObject["Id"].toInt());
                    airplane.setName(jsonObject["Name"].toString());
                    airplane.setDescription(jsonObject["Description"].toString());
                    airplane.setMaxSizeCargo(jsonObject["MaxSizeCargo"].toInt());
                    airplane.setMaxWeightCargo(jsonObject["MaxWeightCargo"].toInt());
                    airplane.setMaxSeatPlaces(jsonObject["MaxSeatPlaces"].toInt());
                    airplane.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(airplane);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane oldAirplane, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldAirplane.getId()));
    query.addQueryItem("Name", airplane.getName());
    query.addQueryItem("Description", airplane.getDescription());
    query.addQueryItem("MaxSizeCargo", QString::number(airplane.getMaxSizeCargo()));
    query.addQueryItem("MaxWeightCargo", QString::number(airplane.getMaxWeightCargo()));
    query.addQueryItem("MaxSeatPlaces", QString::number(airplane.getMaxSeatPlaces()));
    query.addQueryItem("IsDeleted", QString::number(airplane.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterAirplane(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(airplane.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addAirplane(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Airplane airplane)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Airplane/AirplaneSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airplane.getName());
    query.addQueryItem("Description", airplane.getDescription());
    query.addQueryItem("MaxSizeCargo", QString::number(airplane.getMaxSizeCargo()));
    query.addQueryItem("MaxWeightCargo", QString::number(airplane.getMaxWeightCargo()));
    query.addQueryItem("MaxSeatPlaces", QString::number(airplane.getMaxSeatPlaces()));
    query.addQueryItem("IsDeleted", QString::number(airplane.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Airplane

void NetworkAPIRequester::getAllBaggage(const std::function<void(QList<Baggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Baggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Baggage(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Weight"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteBaggage(const std::function<void(QList<Baggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Baggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Baggage(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Weight"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveBaggage(const std::function<void(QList<Baggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Baggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Baggage(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Weight"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchBaggage(const std::function<void (Baggage)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", baggage.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Baggage baggage(0, "", "", 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    baggage.setId(jsonObject["Id"].toInt());
                    baggage.setName(jsonObject["Name"].toString());
                    baggage.setDescription(jsonObject["Description"].toString());
                    baggage.setWeight(jsonObject["Weight"].toInt());
                    baggage.setSize(jsonObject["Size"].toInt());
                    baggage.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(baggage);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage oldBaggage, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldBaggage.getId()));
    query.addQueryItem("Name", baggage.getName());
    query.addQueryItem("Description", baggage.getDescription());
    query.addQueryItem("Weight", QString::number(baggage.getWeight()));
    query.addQueryItem("Size", QString::number(baggage.getSize()));
    query.addQueryItem("IsDeleted", QString::number(baggage.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(baggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(baggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(baggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addBaggage(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Baggage baggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Baggage/BaggageSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", baggage.getName());
    query.addQueryItem("Description", baggage.getDescription());
    query.addQueryItem("Weight", QString::number(baggage.getWeight()));
    query.addQueryItem("Size", QString::number(baggage.getSize()));
    query.addQueryItem("IsDeleted", QString::number(baggage.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Baggage

void NetworkAPIRequester::getAllCargo(const std::function<void(QList<Cargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Cargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Cargo(jsonObject["Id"].toInt(), jsonObject["IdCategory"].toInt(), jsonObject["Weight"].toInt(), jsonObject["Description"].toString(), jsonObject["IdTicket"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteCargo(const std::function<void(QList<Cargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Cargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Cargo(jsonObject["Id"].toInt(), jsonObject["IdCategory"].toInt(), jsonObject["Weight"].toInt(), jsonObject["Description"].toString(), jsonObject["IdTicket"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveCargo(const std::function<void(QList<Cargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Cargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Cargo(jsonObject["Id"].toInt(), jsonObject["IdCategory"].toInt(), jsonObject["Weight"].toInt(), jsonObject["Description"].toString(), jsonObject["IdTicket"].toInt(), jsonObject["Size"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchCargo(const std::function<void (Cargo)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanySearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", cargo.getDescription());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Cargo cargo(0, 0, 0, "", 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    cargo.setId(jsonObject["Id"].toInt());
                    cargo.setIdCategory(jsonObject["IdCategory"].toInt());
                    cargo.setWeight(jsonObject["Weight"].toInt());
                    cargo.setDescription(jsonObject["Description"].toString());
                    cargo.setIdTicket(jsonObject["IdTicket"].toInt());
                    cargo.setSize(jsonObject["Size"].toInt());
                    cargo.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(cargo);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo oldCargo, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldCargo.getId()));
    query.addQueryItem("IdCategory", QString::number(cargo.getIdCategory()));
    query.addQueryItem("IdWeight", QString::number(cargo.getWeight()));
    query.addQueryItem("Description", cargo.getDescription());
    query.addQueryItem("IdTicket", QString::number(cargo.getWeight()));
    query.addQueryItem("Size", QString::number(cargo.getSize()));
    query.addQueryItem("IsDeleted", QString::number(cargo.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(cargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(cargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(cargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addCargo(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Cargo cargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Cargo/CargoSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("IdCategory", QString::number(cargo.getIdCategory()));
    query.addQueryItem("IdWeight", QString::number(cargo.getWeight()));
    query.addQueryItem("Description", cargo.getDescription());
    query.addQueryItem("IdTicket", QString::number(cargo.getWeight()));
    query.addQueryItem("Size", QString::number(cargo.getSize()));
    query.addQueryItem("IsDeleted", QString::number(cargo.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}


//---Cargo

void NetworkAPIRequester::getAllCategoriesCargo(const std::function<void(QList<CategoriesCargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CategoriesCargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CategoriesCargo(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteCategoriesCargo(const std::function<void(QList<CategoriesCargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CategoriesCargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CategoriesCargo(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveCategoriesCargo(const std::function<void(QList<CategoriesCargo>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CategoriesCargo> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CategoriesCargo(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchCategoriesCargo(const std::function<void (CategoriesCargo)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo categoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", categoriesCargo.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        CategoriesCargo categoriesCargo(0, "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    categoriesCargo.setId(jsonObject["Id"].toInt());
                    categoriesCargo.setName(jsonObject["Name"].toString());
                    categoriesCargo.setDescription(jsonObject["Description"].toString());
                    categoriesCargo.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(categoriesCargo);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setCategoriesCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo oldCategoriesCargo, CategoriesCargo categoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldCategoriesCargo.getId()));
    query.addQueryItem("Name", categoriesCargo.getName());
    query.addQueryItem("Description", categoriesCargo.getDescription());
    query.addQueryItem("IsDeleted", QString::number(categoriesCargo.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteCategoriesCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo сategoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(сategoriesCargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverCategoriesCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo сategoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(сategoriesCargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterCategoriesCargo(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo сategoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(сategoriesCargo.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addCategoriesCargo(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CategoriesCargo categoriesCargo)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CategoriesCargo/CategoriesCargoSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", categoriesCargo.getName());
    query.addQueryItem("Description", categoriesCargo.getDescription());
    query.addQueryItem("IsDeleted", QString::number(categoriesCargo.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---CategoriesCargo

void NetworkAPIRequester::getAllClient(const std::function<void(QList<Client>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Client> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Client(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Money"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteClient(const std::function<void(QList<Client>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Client> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Client(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Money"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveClient(const std::function<void(QList<Client>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Client> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Client(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Money"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchClient(const std::function<void (Client)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", client.getFirstName());
    query.addQueryItem("LastName", client.getLastName());
    query.addQueryItem("Patronymic", client.getPatronymic());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Client client(0, "", "", "", 0, 0, 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    client.setId(jsonObject["Id"].toInt());
                    client.setFirstName(jsonObject["FirstName"].toString());
                    client.setLastName(jsonObject["LastName"].toString());
                    client.setPatronymic(jsonObject["Patronymic"].toString());
                    client.setPassportSeries(jsonObject["PassportSeries"].toInt());
                    client.setPassportNumber(jsonObject["PassportNumber"].toInt());
                    client.setAccount(jsonObject["Account"].toInt());
                    client.setMoney(jsonObject["Money"].toInt());
                    client.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(client);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setClient(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client oldClient, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldClient.getId()));
    query.addQueryItem("FirstName", client.getFirstName());
    query.addQueryItem("LastName", client.getLastName());
    query.addQueryItem("Patronymic", client.getPatronymic());
    query.addQueryItem("PassportSeries", QString::number(client.getPassportSeries()));
    query.addQueryItem("PassportNumber", QString::number(client.getPassportNumber()));
    query.addQueryItem("Account", QString::number(client.getAccount()));
    query.addQueryItem("Money", QString::number(client.getMoney()));
    query.addQueryItem("IsDeleted", QString::number(client.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteClient(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(client.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverClient(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(client.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterClient(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(client.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addClient(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Client client)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Client/ClientSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", client.getFirstName());
    query.addQueryItem("LastName", client.getLastName());
    query.addQueryItem("Patronymic", client.getPatronymic());
    query.addQueryItem("PassportSeries", QString::number(client.getPassportSeries()));
    query.addQueryItem("PassportNumber", QString::number(client.getPassportNumber()));
    query.addQueryItem("Account", QString::number(client.getAccount()));
    query.addQueryItem("Money", QString::number(client.getMoney()));
    query.addQueryItem("IsDeleted", QString::number(client.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Client

void NetworkAPIRequester::getAllClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggage(jsonObject["Id"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["IdBaggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggage(jsonObject["Id"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["IdBaggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggage> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggage(jsonObject["Id"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["IdBaggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setClientAndBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggage oldClientAndBaggage, ClientAndBaggage clientAndBaggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldClientAndBaggage.getId()));
    query.addQueryItem("IdClient", QString::number(clientAndBaggage.getIdClient()));
    query.addQueryItem("IdBaggage", QString::number(clientAndBaggage.getIdBaggage()));
    query.addQueryItem("IsDeleted", QString::number(clientAndBaggage.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteClientAndBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggage clientAndBaggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(clientAndBaggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverClientAndBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggage clientAndBaggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(clientAndBaggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterClientAndBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggage clientAndBaggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(clientAndBaggage.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addClientAndBaggage(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggage clientAndBaggage)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggage/ClientAndBaggageSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("IdClient", QString::number(clientAndBaggage.getIdClient()));
    query.addQueryItem("IdBaggage", QString::number(clientAndBaggage.getIdBaggage()));
    query.addQueryItem("IsDeleted", QString::number(clientAndBaggage.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---ClientAndBaggage

void NetworkAPIRequester::getAllFlights(const std::function<void(QList<Flights>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Flights> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Flights(jsonObject["Id"].toInt(), jsonObject["DepartureDate"].toString(), jsonObject["ArrivalDate"].toString(), jsonObject["DeparturePoint"].toInt(), jsonObject["ArrivalPoint"].toInt(), jsonObject["Airplane"].toInt(), jsonObject["Ladder"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteFlights(const std::function<void(QList<Flights>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Flights> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Flights(jsonObject["Id"].toInt(), jsonObject["DepartureDate"].toString(), jsonObject["ArrivalDate"].toString(), jsonObject["DeparturePoint"].toInt(), jsonObject["ArrivalPoint"].toInt(), jsonObject["Airplane"].toInt(), jsonObject["Ladder"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveFlights(const std::function<void(QList<Flights>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Flights> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Flights(jsonObject["Id"].toInt(), jsonObject["DepartureDate"].toString(), jsonObject["ArrivalDate"].toString(), jsonObject["DeparturePoint"].toInt(), jsonObject["ArrivalPoint"].toInt(), jsonObject["Airplane"].toInt(), jsonObject["Ladder"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchFlights(const std::function<void (Flights)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("DepartureDate", flights.getDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Flights flights(0, "", "", 0, 0, 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    flights.setId(jsonObject["Id"].toInt());
                    flights.setDepartureDate(jsonObject["DepartureDate"].toString());
                    flights.setArrivalDate(jsonObject["ArrivalDate"].toString());
                    flights.setDeparturePoint(jsonObject["DeparturePoint"].toInt());
                    flights.setArrivalPoint(jsonObject["ArrivalPoint"].toInt());
                    flights.setDeparturePoint(jsonObject["DeparturePoint"].toInt());
                    flights.setDeparturePoint(jsonObject["Airplane"].toInt());
                    flights.setDeparturePoint(jsonObject["Ladder"].toInt());
                    flights.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(flights);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setFlights(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights oldFlights, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldFlights.getId()));
    query.addQueryItem("DepartureDate", flights.getDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addQueryItem("ArrivalDate", flights.getArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addQueryItem("DeparturePoint", QString::number(flights.getDeparturePoint()));
    query.addQueryItem("ArrivalPoint", QString::number(flights.getArrivalPoint()));
    query.addQueryItem("Airplane", QString::number(flights.getAirplane()));
    query.addQueryItem("Ladder", QString::number(flights.getLadder()));
    query.addQueryItem("IsDeleted", QString::number(flights.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteFlights(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(flights.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverFlights(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(flights.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterFlights(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(flights.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addFlights(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Flights flights)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Flights/FlightsSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("DepartureDate", flights.getDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addQueryItem("ArrivalDate", flights.getArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.addQueryItem("DeparturePoint", QString::number(flights.getDeparturePoint()));
    query.addQueryItem("ArrivalPoint", QString::number(flights.getArrivalPoint()));
    query.addQueryItem("Airplane", QString::number(flights.getAirplane()));
    query.addQueryItem("Ladder", QString::number(flights.getLadder()));
    query.addQueryItem("IsDeleted", QString::number(flights.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Flights

void NetworkAPIRequester::getAllPlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<PlacesOfAirports> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(PlacesOfAirports(jsonObject["Id"].toInt(), jsonObject["Country"].toString(), jsonObject["City"].toString(), jsonObject["Street"].toString(), jsonObject["HouseNumber"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeletePlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<PlacesOfAirports> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(PlacesOfAirports(jsonObject["Id"].toInt(), jsonObject["Country"].toString(), jsonObject["City"].toString(), jsonObject["Street"].toString(), jsonObject["HouseNumber"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActivePlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<PlacesOfAirports> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(PlacesOfAirports(jsonObject["Id"].toInt(), jsonObject["Country"].toString(), jsonObject["City"].toString(), jsonObject["Street"].toString(), jsonObject["HouseNumber"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchPlacesOfAirports(const std::function<void (PlacesOfAirports)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Country", placesOfAirports.getCountry());
    query.addQueryItem("City", placesOfAirports.getCity());
    query.addQueryItem("Street", placesOfAirports.getStreet());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        PlacesOfAirports placesOfAirports(0, "", "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    placesOfAirports.setId(jsonObject["Id"].toInt());
                    placesOfAirports.setCountry(jsonObject["Contry"].toString());
                    placesOfAirports.setCity(jsonObject["City"].toString());
                    placesOfAirports.setStreet(jsonObject["Street"].toString());
                    placesOfAirports.setHouseNumber(jsonObject["HouseNumber"].toInt());
                    placesOfAirports.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(placesOfAirports);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setPlacesOfAirports(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports oldPlacesOfAirports, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldPlacesOfAirports.getId()));
    query.addQueryItem("Country", placesOfAirports.getCountry());
    query.addQueryItem("City", placesOfAirports.getCity());
    query.addQueryItem("Street", placesOfAirports.getStreet());
    query.addQueryItem("HouseNumber", QString::number(placesOfAirports.getHouseNumber()));
    query.addQueryItem("IsDeleted", QString::number(placesOfAirports.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deletePlacesOfAirports(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(placesOfAirports.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverPlacesOfAirports(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(placesOfAirports.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterPlacesOfAirports(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(placesOfAirports.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addPlacesOfAirports(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, PlacesOfAirports placesOfAirports)
{
    QNetworkRequest request(QUrl(this->url + "Tables/PlacesOfAirports/PlacesOfAirportsSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Country", placesOfAirports.getCountry());
    query.addQueryItem("City", placesOfAirports.getCity());
    query.addQueryItem("Street", placesOfAirports.getStreet());
    query.addQueryItem("HouseNumber", QString::number(placesOfAirports.getHouseNumber()));
    query.addQueryItem("IsDeleted", QString::number(placesOfAirports.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---PlacesOfAirports

void NetworkAPIRequester::getAllPost(const std::function<void(QList<Post>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Post> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Post(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Salary"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeletePost(const std::function<void(QList<Post>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Post> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Post(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Salary"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActivePost(const std::function<void(QList<Post>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Post> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Post(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Salary"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchPost(const std::function<void (Post)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", post.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Post post(0, "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    post.setId(jsonObject["Id"].toInt());
                    post.setName(jsonObject["Name"].toString());
                    post.setId(jsonObject["Salary"].toInt());
                    post.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(post);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setPost(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post oldPost, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldPost.getId()));
    query.addQueryItem("Name", post.getName());
    query.addQueryItem("Salary", QString::number(post.getSalary()));
    query.addQueryItem("IsDeleted", QString::number(post.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deletePost(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(post.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverPost(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(post.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterPost(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(post.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addPost(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Post post)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Post/PostSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", post.getName());
    query.addQueryItem("Salary", QString::number(post.getSalary()));
    query.addQueryItem("IsDeleted", QString::number(post.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Post

void NetworkAPIRequester::getAllServices(const std::function<void(QList<Services>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Services> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Services(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Price"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteServices(const std::function<void(QList<Services>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Services> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Services(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Price"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveServices(const std::function<void(QList<Services>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Services> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Services(jsonObject["Id"].toInt(), jsonObject["Name"].toString(), jsonObject["Description"].toString(), jsonObject["Price"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchServices(const std::function<void (Services)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", services.getName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Services services(0, "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    services.setId(jsonObject["Id"].toInt());
                    services.setName(jsonObject["Name"].toString());
                    services.setDescription(jsonObject["Description"].toString());
                    services.setPrice(jsonObject["Price"].toInt());
                    services.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(services);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services oldServices, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldServices.getId()));
    query.addQueryItem("Name", services.getName());
    query.addQueryItem("Description", services.getDescription());
    query.addQueryItem("Price", QString::number(services.getPrice()));
    query.addQueryItem("IsDeleted", QString::number(services.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(services.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(services.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(services.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addServices(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Services services)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Services/ServicesSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", services.getName());
    query.addQueryItem("Description", services.getDescription());
    query.addQueryItem("Price", QString::number(services.getPrice()));
    query.addQueryItem("IsDeleted", QString::number(services.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---Services

void NetworkAPIRequester::getAllStaff(const std::function<void(QList<Staff>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Staff> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Staff(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["Post"].toInt(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Education"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteStaff(const std::function<void(QList<Staff>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Staff> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Staff(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["Post"].toInt(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Education"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveStaff(const std::function<void(QList<Staff>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Staff> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Staff(jsonObject["Id"].toInt(), jsonObject["FirstName"].toString(), jsonObject["LastName"].toString(), jsonObject["Patronymic"].toString(), jsonObject["Post"].toInt(), jsonObject["PassportSeries"].toInt(), jsonObject["PassportNumber"].toInt(), jsonObject["Account"].toInt(), jsonObject["Education"].toString(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchStaff(const std::function<void (Staff)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", staff.getFirstName());
    query.addQueryItem("LastName", staff.getLastName());
    query.addQueryItem("Patronymic", staff.getPatronymic());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Staff staff(0, "", "", "", 0, 0, 0, 0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    staff.setId(jsonObject["Id"].toInt());
                    staff.setFirstName(jsonObject["FirstName"].toString());
                    staff.setLastName(jsonObject["LastName"].toString());
                    staff.setPatronymic(jsonObject["Patronymic"].toString());
                    staff.setPost(jsonObject["Post"].toInt());
                    staff.setPassportSeries(jsonObject["PassportSeries"].toInt());
                    staff.setPassportNumber(jsonObject["PassportNumber"].toInt());
                    staff.setAccount(jsonObject["Account"].toInt());
                    staff.setEducation(jsonObject["Education"].toString());
                    staff.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(staff);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setStaff(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff oldStaff, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldStaff.getId()));
    query.addQueryItem("FirstName", staff.getFirstName());
    query.addQueryItem("LastName", staff.getLastName());
    query.addQueryItem("Patronymic", staff.getPatronymic());
    query.addQueryItem("Post", QString::number(staff.getPost()));
    query.addQueryItem("PassportSeries", QString::number(staff.getPassportSeries()));
    query.addQueryItem("PassportNumber", QString::number(staff.getPassportNumber()));
    query.addQueryItem("Account", QString::number(staff.getAccount()));
    query.addQueryItem("Education", staff.getEducation());
    query.addQueryItem("IsDeleted", QString::number(staff.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteStaff(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(staff.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverStaff(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(staff.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterStaff(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(staff.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addStaff(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Staff staff)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Staff/StaffSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", staff.getFirstName());
    query.addQueryItem("LastName", staff.getLastName());
    query.addQueryItem("Patronymic", staff.getPatronymic());
    query.addQueryItem("Post", QString::number(staff.getPost()));
    query.addQueryItem("PassportSeries", QString::number(staff.getPassportSeries()));
    query.addQueryItem("PassportNumber", QString::number(staff.getPassportNumber()));
    query.addQueryItem("Account", QString::number(staff.getAccount()));
    query.addQueryItem("Education", staff.getEducation());
    query.addQueryItem("IsDeleted", QString::number(staff.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}


//---Staff

void NetworkAPIRequester::getAllTickets(const std::function<void(QList<Tickets>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Tickets> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Tickets(jsonObject["Id"].toInt(), jsonObject["Price"].toInt(), jsonObject["SeatNumber"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["Flights"].toInt(), jsonObject["BaggageAvailable"].toInt() == 1, jsonObject["Baggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTickets(const std::function<void(QList<Tickets>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Tickets> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Tickets(jsonObject["Id"].toInt(), jsonObject["Price"].toInt(), jsonObject["SeatNumber"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["Flights"].toInt(), jsonObject["BaggageAvailable"].toInt() == 1, jsonObject["Baggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTickets(const std::function<void(QList<Tickets>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<Tickets> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(Tickets(jsonObject["Id"].toInt(), jsonObject["Price"].toInt(), jsonObject["SeatNumber"].toInt(), jsonObject["IdClient"].toInt(), jsonObject["Flights"].toInt(), jsonObject["BaggageAvailable"].toInt() == 1, jsonObject["Baggage"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchTickets(const std::function<void (Tickets)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("SeatNumber", QString::number(tickets.getSeatNumber()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        Tickets tickets(0, 0, 0, 0, 0, false, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    tickets.setId(jsonObject["Id"].toInt());
                    tickets.setPrice(jsonObject["Price"].toInt());
                    tickets.setIdClient(jsonObject["IdClient"].toInt());
                    tickets.setSeatNumber(jsonObject["SeatNumber"].toInt());
                    tickets.setFlights(jsonObject["Flights"].toInt());
                    tickets.setBaggageAvailable(jsonObject["BaggageAvailable"].toInt() == 1);
                    tickets.setBaggage(jsonObject["Baggage"].toInt());
                    tickets.setIsDeleted(jsonObject["IsDeleted"].toInt() == 1);
            }

            callBackSuccess(tickets);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setTickets(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets oldTickets, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldTickets.getId()));
    query.addQueryItem("Price", QString::number(tickets.getPrice()));
    query.addQueryItem("IdClient", QString::number(tickets.getIdClient()));
    query.addQueryItem("SeatNumber", QString::number(tickets.getSeatNumber()));
    query.addQueryItem("Flights", QString::number(tickets.getFlights()));
    query.addQueryItem("BaggageAvailable", QString::number(tickets.getBaggageAvailable()));
    query.addQueryItem("Baggage", QString::number(tickets.getBaggage()));
    query.addQueryItem("IsDeleted", QString::number(tickets.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteTickets(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(tickets.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverTickets(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(tickets.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterTickets(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/Tickets/TicketsLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(tickets.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addTickets(const std::function<void(unsigned int)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, Tickets tickets)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServices/AirCompanyAndServicesSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Price", QString::number(tickets.getPrice()));
    query.addQueryItem("IdClient", QString::number(tickets.getIdClient()));
    query.addQueryItem("SeatNumber", QString::number(tickets.getSeatNumber()));
    query.addQueryItem("Flights", QString::number(tickets.getFlights()));
    query.addQueryItem("BaggageAvailable", QString::number(tickets.getBaggageAvailable()));
    query.addQueryItem("Baggage", QString::number(tickets.getBaggage()));
    query.addQueryItem("IsDeleted", QString::number(tickets.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(jsonObject["Id"].toInt());
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}


//---Tickets

void NetworkAPIRequester::getAllTicketsAndServices(const std::function<void(QList<TicketsAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServices(jsonObject["Id"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IdTicket"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTicketsAndServices(const std::function<void(QList<TicketsAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServices(jsonObject["Id"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IdTicket"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTicketsAndServices(const std::function<void(QList<TicketsAndServices>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServices> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServices(jsonObject["Id"].toInt(), jsonObject["IdService"].toInt(), jsonObject["IdTicket"].toInt(), jsonObject["IsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::setTicketsAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServices oldTicketsAndServices, TicketsAndServices ticketsAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesChange.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(oldTicketsAndServices.getId()));
    query.addQueryItem("IdService", QString::number(ticketsAndServices.getIdService()));
    query.addQueryItem("IdTicket", QString::number(ticketsAndServices.getIdTicket()));
    query.addQueryItem("IsDeleted", QString::number(ticketsAndServices.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::deleteTicketsAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServices ticketsAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesDelete.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(ticketsAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalRecoverTicketsAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServices ticketsAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesLogicalRecover.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(ticketsAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::logicalDeleterTicketsAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServices ticketsAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesLogicalDeleter.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Id", QString::number(ticketsAndServices.getId()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::addTicketsAndServices(const std::function<void (bool)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServices ticketsAndServices)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServices/TicketsAndServicesSender.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("IdService", QString::number(ticketsAndServices.getIdService()));
    query.addQueryItem("IdTicket", QString::number(ticketsAndServices.getIdTicket()));
    query.addQueryItem("IsDeleted", QString::number(ticketsAndServices.getIsDeleted()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            callBackSuccess(true);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---TicketsAndServices

void NetworkAPIRequester::getAllAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneFull/AirCompanyAndAirplaneFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneFull(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneFull/AirCompanyAndAirplaneFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneFull(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneFull/AirCompanyAndAirplaneFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneFull(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirCompanyAndAirplaneFull(const std::function<void (AirCompanyAndAirplaneFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplaneFull airCompanyAndAirplaneFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneFull/AirCompanyAndAirplaneFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompanyAndAirplaneFull.getAirplaneName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        AirCompanyAndAirplaneFull airCompanyAndAirplaneFull(0, "", "", 0, 0, 0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airCompanyAndAirplaneFull.setAirplaneId(jsonObject["AirplaneId"].toInt());
                    airCompanyAndAirplaneFull.setAirplaneName(jsonObject["AirplaneName"].toString());
                    airCompanyAndAirplaneFull.setAirplaneDescription(jsonObject["AirplaneDescription"].toString());
                    airCompanyAndAirplaneFull.setAirplaneMaxSizeCargo(jsonObject["AirplaneMaxSizeCargo"].toInt());
                    airCompanyAndAirplaneFull.setAirplaneMaxWeightCargo(jsonObject["AirplaneMaxWeightCargo"].toInt());
                    airCompanyAndAirplaneFull.setAirplaneMaxSeatPlaces(jsonObject["AirplaneMaxSeatPlaces"].toInt());
                    airCompanyAndAirplaneFull.setAirCompanyName(jsonObject["AirCompanyName"].toString());
                    airCompanyAndAirplaneFull.setAirplaneIsDeleted(jsonObject["AirplaneIsDeleted"].toInt() == 1);
            }

            callBackSuccess(airCompanyAndAirplaneFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndAirplaneFull

void NetworkAPIRequester::getAllAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneTrunc/AirCompanyAndAirplaneTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneTrunc(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneTrunc/AirCompanyAndAirplaneTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneTrunc(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneTrunc/AirCompanyAndAirplaneTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndAirplaneTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndAirplaneTrunc(jsonObject["AirplaneId"].toInt(), jsonObject["AirplaneName"].toString(), jsonObject["AirCompanyName"].toString(), jsonObject["AirplaneIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirCompanyAndAirplaneTrunc(const std::function<void (AirCompanyAndAirplaneTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndAirplaneTrunc airCompanyAndAirplaneTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndAirplaneTrunc/AirCompanyAndAirplaneTruncySearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompanyAndAirplaneTrunc.getAirplaneName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        AirCompanyAndAirplaneTrunc airCompanyAndAirplaneTrunc(0, "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airCompanyAndAirplaneTrunc.setAirplaneId(jsonObject["AirplaneId"].toInt());
                    airCompanyAndAirplaneTrunc.setAirplaneName(jsonObject["AirplaneName"].toString());
                    airCompanyAndAirplaneTrunc.setAirCompanyName(jsonObject["AirCompanyName"].toString());
                    airCompanyAndAirplaneTrunc.setAirplaneIsDeleted(jsonObject["AirplaneIsDeleted"].toInt() == 1);
            }

            callBackSuccess(airCompanyAndAirplaneTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndAirplaneTrunc

void NetworkAPIRequester::getAllAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesFull/AirCompanyAndServicesFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesFull(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServiceDescription"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesFull/AirCompanyAndServicesFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesFull(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServiceDescription"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesFull/AirCompanyAndServicesFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesFull(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServiceDescription"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirCompanyAndServicesFull(const std::function<void (AirCompanyAndServicesFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServicesFull airCompanyAndServicesFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompany/AirCompanySearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompanyAndServicesFull.getServiceName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        AirCompanyAndServicesFull airCompanyAndServicesFull(0, "", "", 0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airCompanyAndServicesFull.setServicesId(jsonObject["ServiceId"].toInt());
                    airCompanyAndServicesFull.setServiceName(jsonObject["ServiceName"].toString());
                    airCompanyAndServicesFull.setServiceDescription(jsonObject["ServiceDescription"].toString());
                    airCompanyAndServicesFull.setServicePrice(jsonObject["ServicePrice"].toInt());
                    airCompanyAndServicesFull.setAirCompanyName(jsonObject["AirCompanyName"].toString());
                    airCompanyAndServicesFull.setServicesIsDeleted(jsonObject["ServicesIsDeleted"].toInt() == 1);
            }

            callBackSuccess(airCompanyAndServicesFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndServicesFull

void NetworkAPIRequester::getAllAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesTrunc/AirCompanyAndServicesTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesTrunc(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesTrunc/AirCompanyAndServicesTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesTrunc(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesTrunc/AirCompanyAndServicesTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<AirCompanyAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(AirCompanyAndServicesTrunc(jsonObject["ServiceId"].toInt(), jsonObject["ServiceName"].toString(), jsonObject["ServicePrice"].toInt(), jsonObject["AirCompanyName"].toString(), jsonObject["ServicesIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchAirCompanyAndServicesTrunc(const std::function<void (AirCompanyAndServicesTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, AirCompanyAndServicesTrunc airCompanyAndServicesTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesTrunc/AirCompanyAndServicesTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", airCompanyAndServicesTrunc.getServiceName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        AirCompanyAndServicesTrunc airCompanyAndServicesTrunc(0, "", 0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    airCompanyAndServicesTrunc.setServicesId(jsonObject["ServiceId"].toInt());
                    airCompanyAndServicesTrunc.setServiceName(jsonObject["ServiceName"].toString());
                    airCompanyAndServicesTrunc.setServicePrice(jsonObject["ServicePrice"].toInt());
                    airCompanyAndServicesTrunc.setAirCompanyName(jsonObject["AirCompanyName"].toString());
                    airCompanyAndServicesTrunc.setServicesIsDeleted(jsonObject["ServicesIsDeleted"].toInt() == 1);
            }

            callBackSuccess(airCompanyAndServicesTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---AirCompanyAndServicesTrunc

void NetworkAPIRequester::getAllCargoFull(const std::function<void(QList<CargoFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoFull/CargoFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoFull(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymicName"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteCargoFull(const std::function<void(QList<CargoFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoFull/CargoFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoFull(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymicName"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveCargoFull(const std::function<void(QList<CargoFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoFull/CargoFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoFull(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymicName"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchCargoFull(const std::function<void (CargoFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CargoFull cargoFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoFull/CargoFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Description", cargoFull.getCargoDescription());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        CargoFull cargoFull(0, "", 0, 0, "", "", "", "", 0, 0, "", "", "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    cargoFull.setCargoId(jsonObject["CargoId"].toInt());
                    cargoFull.setCargoDescription(jsonObject["CargoDescription"].toString());
                    cargoFull.setCargoWeight(jsonObject["CargoWeight"].toInt());
                    cargoFull.setCargoSize(jsonObject["CargoSize"].toInt());
                    cargoFull.setCategoriesCargoName(jsonObject["CategoriesCargoName"].toString());
                    cargoFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    cargoFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    cargoFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    cargoFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    cargoFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    cargoFull.setFlightsArrivalDate(jsonObject["FlightsArrivalDate"].toString());
                    cargoFull.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    cargoFull.setDeparturePoint(jsonObject["DeparturePoint"].toString());
                    cargoFull.setArrivalPoint(jsonObject["ArrivalPoint"].toString());
                    cargoFull.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    cargoFull.setCargoIsDeleted(jsonObject["CargoIsDeleted"].toInt() == 1);
            }

            callBackSuccess(cargoFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---CargoFull

void NetworkAPIRequester::getAllCargoTrunc(const std::function<void(QList<CargoTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoTrunc/CargoTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoTrunc(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteCargoTrunc(const std::function<void(QList<CargoTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoTrunc/CargoTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoTrunc(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveCargoTrunc(const std::function<void(QList<CargoTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoTrunc/CargoTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<CargoTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(CargoTrunc(jsonObject["CargoId"].toInt(), jsonObject["CargoDescription"].toString(), jsonObject["CargoWeight"].toInt(), jsonObject["CargoSize"].toInt(), jsonObject["CategoriesCargoName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["CargoIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchCargoTrunc(const std::function<void (CargoTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, CargoTrunc cargoTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/CargoTrunc/CargoTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Description", cargoTrunc.getCargoDescription());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        CargoTrunc cargoTrunc(0, "", 0, 0, "", "", "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    cargoTrunc.setCargoId(jsonObject["CargoId"].toInt());
                    cargoTrunc.setCargoDescription(jsonObject["CargoDescription"].toString());
                    cargoTrunc.setCargoWeight(jsonObject["CargoWeight"].toInt());
                    cargoTrunc.setCargoWeight(jsonObject["CargoSize"].toInt());
                    cargoTrunc.setCategoriesCargoName(jsonObject["CategoriesCargoName"].toString());
                    cargoTrunc.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    cargoTrunc.setClientLastName(jsonObject["ClientLastName"].toString());
                    cargoTrunc.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    cargoTrunc.setCargoIsDeleted(jsonObject["CargoIsDeleted"].toInt() == 1);
            }

            callBackSuccess(cargoTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---CargoTrunc

void NetworkAPIRequester::getAllClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageFull/ClientAndBaggageFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageFull(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageFull/ClientAndBaggageFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageFull(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageFull/ClientAndBaggageFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageFull(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchClientAndBaggageFull(const std::function<void (ClientAndBaggageFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggageFull clientAndBaggageFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageFull/ClientAndBaggageFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", clientAndBaggageFull.getBaggageName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        ClientAndBaggageFull clientAndBaggageFull(0, "", "", 0, 0, "", "", "", 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    clientAndBaggageFull.setBaggageId(jsonObject["BaggageId"].toInt());
                    clientAndBaggageFull.setBaggageName(jsonObject["BaggageName"].toString());
                    clientAndBaggageFull.setBaggageDescription(jsonObject["BaggageDescription"].toString());
                    clientAndBaggageFull.setBaggageWeight(jsonObject["BaggageWeight"].toInt());
                    clientAndBaggageFull.setBaggageSize(jsonObject["BaggageSize"].toInt());
                    clientAndBaggageFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    clientAndBaggageFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    clientAndBaggageFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    clientAndBaggageFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    clientAndBaggageFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    clientAndBaggageFull.setBaggageIsDeleted(jsonObject["BaggageIsDeleted"].toInt() == 1);
            }

            callBackSuccess(clientAndBaggageFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---ClientAndBaggageFull

void NetworkAPIRequester::getAllClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageTrunc/ClientAndBaggageTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageTrunc(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageTrunc/ClientAndBaggageTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageTrunc(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageTrunc/ClientAndBaggageTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientAndBaggageTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientAndBaggageTrunc(jsonObject["BaggageId"].toInt(), jsonObject["BaggageName"].toString(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["BaggageIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchClientAndBaggageTrunc(const std::function<void (ClientAndBaggageTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientAndBaggageTrunc clientAndBaggageTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/ClientAndBaggageTrunc/ClientAndBaggageTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Name", clientAndBaggageTrunc.getBaggageName());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        ClientAndBaggageTrunc clientAndBaggageTrunc(0, "", "", "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    clientAndBaggageTrunc.setBaggageId(jsonObject["BaggageId"].toInt());
                    clientAndBaggageTrunc.setBaggageName(jsonObject["BaggageName"].toString());
                    clientAndBaggageTrunc.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    clientAndBaggageTrunc.setClientLastName(jsonObject["ClientLastName"].toString());
                    clientAndBaggageTrunc.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    clientAndBaggageTrunc.setBaggageIsDeleted(jsonObject["BaggageIsDeleted"].toInt() == 1);
            }

            callBackSuccess(clientAndBaggageTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---ClientAndBaggageTrunc

void NetworkAPIRequester::getAllFlightsFull(const std::function<void(QList<FlightsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsFull/FlightsFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsFull(jsonObject["FlightsId"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["DeparturePoint"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteFlightsFull(const std::function<void(QList<FlightsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsFull/FlightsFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsFull(jsonObject["FlightsId"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["DeparturePoint"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveFlightsFull(const std::function<void(QList<FlightsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsFull/FlightsFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsFull(jsonObject["FlightsId"].toInt(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["DeparturePoint"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxWeightCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchFlightsFull(const std::function<void (FlightsFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, FlightsFull flightsFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsFull/FlightsFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("DepartureDate", flightsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        FlightsFull flightsFull(0, "", "", "", "", "", "", 0, 0, 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    flightsFull.setFlightsId(jsonObject["FlightsId"].toInt());
                    flightsFull.setFlightsArrivalDate(jsonObject["FlightsArrivalDate"].toString());
                    flightsFull.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    flightsFull.setArrivalPoint(jsonObject["ArrivalPoint"].toString());
                    flightsFull.setDeparturePoint(jsonObject["DeparturePoint"].toString());
                    flightsFull.setAirplaneName(jsonObject["AirplaneName"].toString());
                    flightsFull.setAirplaneDescription(jsonObject["AirplaneDescription"].toString());
                    flightsFull.setAirplaneMaxSizeCargo(jsonObject["AirplaneMaxSizeCargo"].toInt());
                    flightsFull.setAirplaneMaxWeightCargo(jsonObject["AirplaneMaxWeightCargo"].toInt());
                    flightsFull.setAirplaneMaxSeatPlaces(jsonObject["AirplaneMaxSeatPlaces"].toInt());
                    flightsFull.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    flightsFull.setFlightsIsDeleted(jsonObject["FlightsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(flightsFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---FlightsFull

void NetworkAPIRequester::getAllFlightsTrunc(const std::function<void(QList<FlightsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsTrunc/FlightsTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsTrunc(jsonObject["FlightsId"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteFlightsTrunc(const std::function<void(QList<FlightsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsTrunc/FlightsTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsTrunc(jsonObject["FlightsId"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveFlightsTrunc(const std::function<void(QList<FlightsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsTrunc/FlightsTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<FlightsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(FlightsTrunc(jsonObject["FlightsId"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["ArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["FlightsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchFlightsTrunc(const std::function<void (FlightsTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, FlightsTrunc flightsTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/FlightsTrunc/FlightsTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("DepartureDate", flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        FlightsTrunc flightsTrunc(0, "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    flightsTrunc.setFlightsId(jsonObject["FlightsId"].toInt());
                    flightsTrunc.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    flightsTrunc.setArrivalPoint(jsonObject["ArrivalPoint"].toString());
                    flightsTrunc.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    flightsTrunc.setFlightsIsDeleted(jsonObject["FlightsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(flightsTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---FlightsTrunc

void NetworkAPIRequester::getAllStaffFull(const std::function<void(QList<StaffFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffFull/StaffFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffFull(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffPassportSeries"].toInt(), jsonObject["StaffPassportNumber"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteStaffFull(const std::function<void(QList<StaffFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffFull/StaffFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffFull(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffPassportSeries"].toInt(), jsonObject["StaffPassportNumber"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveStaffFull(const std::function<void(QList<StaffFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffFull/StaffFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffFull(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffPassportSeries"].toInt(), jsonObject["StaffPassportNumber"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchStaffFull(const std::function<void (StaffFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, StaffFull staffFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffFull/StaffFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", staffFull.getStaffFirstName());
    query.addQueryItem("LastName", staffFull.getStaffLastName());
    query.addQueryItem("Patronymic", staffFull.getStaffPatronymic());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        StaffFull staffFull(0, "", "", "", "", 0, 0, 0, "", "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    staffFull.setStaffId(jsonObject["StaffId"].toInt());
                    staffFull.setStaffFirstName(jsonObject["StaffFirstName"].toString());
                    staffFull.setStaffLastName(jsonObject["StaffLastName"].toString());
                    staffFull.setStaffPatronymic(jsonObject["StaffPatronymic"].toString());
                    staffFull.setPostName(jsonObject["PostName"].toString());
                    staffFull.setPostSalary(jsonObject["PostSalary"].toInt());
                    staffFull.setStaffPassportSeries(jsonObject["StaffPassportSeries"].toInt());
                    staffFull.setStaffPassportNumber(jsonObject["StaffPassportNumber"].toInt());
                    staffFull.setStaffEducation(jsonObject["StaffEducation"].toString());
                    staffFull.setAccountLogin(jsonObject["AccountLogin"].toString());
                    staffFull.setAccountPassword(jsonObject["AccountPassword"].toString());
                    staffFull.setStaffIsDeleted(jsonObject["StaffIsDeleted"].toInt() == 1);
            }

            callBackSuccess(staffFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

void NetworkAPIRequester::searchByLoginStaffFull(const std::function<void (StaffFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, StaffFull staffFull)
{
    QNetworkRequest request(QUrl(this->url + "Views/StaffFull/StaffFullSearchByLogin.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Login", staffFull.getAccountLogin());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        StaffFull staffFull(0, "", "", "", "", 0, 0, 0, "", "", "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    staffFull.setStaffId(jsonObject["StaffId"].toInt());
                    staffFull.setStaffFirstName(jsonObject["StaffFirstName"].toString());
                    staffFull.setStaffLastName(jsonObject["StaffLastName"].toString());
                    staffFull.setStaffPatronymic(jsonObject["StaffPatronymic"].toString());
                    staffFull.setPostName(jsonObject["PostName"].toString());
                    staffFull.setPostSalary(jsonObject["PostSalary"].toInt());
                    staffFull.setStaffPassportSeries(jsonObject["StaffPassportSeries"].toInt());
                    staffFull.setStaffPassportNumber(jsonObject["StaffPassportNumber"].toInt());
                    staffFull.setStaffEducation(jsonObject["StaffEducation"].toString());
                    staffFull.setAccountLogin(jsonObject["AccountLogin"].toString());
                    staffFull.setAccountPassword(jsonObject["AccountPassword"].toString());
                    staffFull.setStaffIsDeleted(jsonObject["StaffIsDeleted"].toInt() == 1);
            }

            callBackSuccess(staffFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---StaffFull

void NetworkAPIRequester::getAllStaffTrunc(const std::function<void(QList<StaffTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffTrunc/StaffTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffTrunc(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteStaffTrunc(const std::function<void(QList<StaffTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffTrunc/StaffTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffTrunc(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveStaffTrunc(const std::function<void(QList<StaffTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffTrunc/StaffTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<StaffTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(StaffTrunc(jsonObject["StaffId"].toInt(), jsonObject["StaffFirstName"].toString(), jsonObject["StaffLastName"].toString(), jsonObject["StaffPatronymic"].toString(), jsonObject["PostName"].toString(), jsonObject["PostSalary"].toInt(), jsonObject["StaffEducation"].toString(), jsonObject["StaffIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchStaffTrunc(const std::function<void (StaffTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, StaffTrunc staffTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/StaffTrunc/StaffTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", staffTrunc.getStaffFirstName());
    query.addQueryItem("LastName", staffTrunc.getStaffLastName());
    query.addQueryItem("Patronymic", staffTrunc.getStaffPatronymic());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        StaffTrunc staffTrunc(0, "", "", "", "", 0, "", false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    staffTrunc.setStaffId(jsonObject["StaffId"].toInt());
                    staffTrunc.setStaffFirstName(jsonObject["StaffFirstName"].toString());
                    staffTrunc.setStaffLastName(jsonObject["StaffLastName"].toString());
                    staffTrunc.setStaffPatronymic(jsonObject["StaffPatronymic"].toString());
                    staffTrunc.setPostName(jsonObject["PostName"].toString());
                    staffTrunc.setPostSalary(jsonObject["PostSalary"].toInt());
                    staffTrunc.setStaffEducation(jsonObject["StaffEducation"].toString());
                    staffTrunc.setStaffIsDeleted(jsonObject["StaffIsDeleted"].toInt() == 1);
            }

            callBackSuccess(staffTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---StaffTrunc

void NetworkAPIRequester::getAllTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesFull/TicketsAndServicesFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ServicesName"].toString(), jsonObject["ServicesDescription"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesFull/TicketsAndServicesFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ServicesName"].toString(), jsonObject["ServicesDescription"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesFull/TicketsAndServicesFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["ServicesName"].toString(), jsonObject["ServicesDescription"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchTicketsAndServicesFull(const std::function<void (TicketsAndServicesFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServicesFull ticketsAndServicesFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesFull/TicketsAndServicesFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("SeatNumber", QString::number(ticketsAndServicesFull.getTicketsSeatNumber()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        TicketsAndServicesFull ticketsAndServicesFull(0, 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, "", "", 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    ticketsAndServicesFull.setTicketsId(jsonObject["TicketsId"].toInt());
                    ticketsAndServicesFull.setTicketsPrice(jsonObject["TicketsPrice"].toInt());
                    ticketsAndServicesFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    ticketsAndServicesFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    ticketsAndServicesFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    ticketsAndServicesFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    ticketsAndServicesFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    ticketsAndServicesFull.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    ticketsAndServicesFull.setFlightsArrivalDate(jsonObject["FlightsArrivalDate"].toString());
                    ticketsAndServicesFull.setDeparturePoint(jsonObject["FlightsDeparturePoint"].toString());
                    ticketsAndServicesFull.setArrivalPoint(jsonObject["FlightsArrivalPoint"].toString());
                    ticketsAndServicesFull.setAirplaneName(jsonObject["AirplaneName"].toString());
                    ticketsAndServicesFull.setAirplaneDescription(jsonObject["AirplaneDescription"].toString());
                    ticketsAndServicesFull.setAirplaneMaxSizeCargo(jsonObject["AirplaneMaxSizeCargo"].toInt());
                    ticketsAndServicesFull.setAirplaneMaxWeightCargo(jsonObject["AirplaneMaxWeightCargo"].toInt());
                    ticketsAndServicesFull.setAirplaneMaxSeatPlaces(jsonObject["AirplaneMaxSeatPlaces"].toInt());
                    ticketsAndServicesFull.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    ticketsAndServicesFull.setTicketsBaggageAvailable(jsonObject["TicketsBaggageAvailable"].toInt() == 1);
                    ticketsAndServicesFull.setBaggageName(jsonObject["BaggageName"].toString());
                    ticketsAndServicesFull.setBaggageDescription(jsonObject["BaggageDescription"].toString());
                    ticketsAndServicesFull.setBaggageWeight(jsonObject["BaggageWeight"].toInt());
                    ticketsAndServicesFull.setBaggageSize(jsonObject["BaggageSize"].toInt());
                    ticketsAndServicesFull.setServicesName(jsonObject["ServicesName"].toString());
                    ticketsAndServicesFull.setServicesDescription(jsonObject["ServicesDescription"].toString());
                    ticketsAndServicesFull.setServicesPrice(jsonObject["ServicesPrice"].toInt());
                    ticketsAndServicesFull.setTicketsSeatNumber(jsonObject["TicketsSeatNumber"].toInt());
                    ticketsAndServicesFull.setTicketsIsDeleted(jsonObject["TicketsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(ticketsAndServicesFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---TicketsAndServicesFull

void NetworkAPIRequester::getAllTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/AirCompanyAndServicesTrunc/TicketsAndServicesTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ServicesName"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesTrunc/TicketsAndServicesTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ServicesName"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesTrunc/TicketsAndServicesTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsAndServicesTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsAndServicesTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ServicesName"].toString(), jsonObject["ServicesPrice"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchTicketsAndServicesTrunc(const std::function<void (TicketsAndServicesTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsAndServicesTrunc ticketsAndServicesTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsAndServicesTrunc/TicketsAndServicesTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("SeatNumber", QString::number(ticketsAndServicesTrunc.getTicketsSeatNumber()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        TicketsAndServicesTrunc ticketsAndServicesTrunc(0, 0, "", "", "", "", 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    ticketsAndServicesTrunc.setTicketsId(jsonObject["TicketsId"].toInt());
                    ticketsAndServicesTrunc.setTicketsPrice(jsonObject["TicketsPrice"].toInt());
                    ticketsAndServicesTrunc.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    ticketsAndServicesTrunc.setClientLastName(jsonObject["ClientLastName"].toString());
                    ticketsAndServicesTrunc.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    ticketsAndServicesTrunc.setServicesName(jsonObject["ServicesName"].toString());
                    ticketsAndServicesTrunc.setServicesPrice(jsonObject["ServicesPrice"].toInt());
                    ticketsAndServicesTrunc.setTicketsSeatNumber(jsonObject["TicketsSeatNumber"].toInt());
                    ticketsAndServicesTrunc.setTicketsIsDeleted(jsonObject["TicketsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(ticketsAndServicesTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---TicketsAndServicesTrunc

void NetworkAPIRequester::getAllTicketsFull(const std::function<void(QList<TicketsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsFull/TicketsFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTicketsFull(const std::function<void(QList<TicketsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsFull/TicketsFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTicketsFull(const std::function<void(QList<TicketsFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsFull/TicketsFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsFull(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalDate"].toString(), jsonObject["FlightsDeparturePoint"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["AirplaneName"].toString(), jsonObject["AirplaneDescription"].toString(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSizeCargo"].toInt(), jsonObject["AirplaneMaxSeatPlaces"].toInt(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["BaggageDescription"].toString(), jsonObject["BaggageWeight"].toInt(), jsonObject["BaggageSize"].toInt(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchTicketsFull(const std::function<void (TicketsFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsFull ticketsFull)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsFull/TicketsFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("SeatNumber", QString::number(ticketsFull.getTicketsSeatNumber()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        TicketsFull ticketsFull(0, 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    ticketsFull.setTicketsId(jsonObject["TicketsId"].toInt());
                    ticketsFull.setTicketsPrice(jsonObject["TicketsPrice"].toInt());
                    ticketsFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    ticketsFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    ticketsFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    ticketsFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    ticketsFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    ticketsFull.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    ticketsFull.setFlightsArrivalDate(jsonObject["FlightsArrivalDate"].toString());
                    ticketsFull.setDeparturePoint(jsonObject["FlightsDeparturePoint"].toString());
                    ticketsFull.setArrivalPoint(jsonObject["FlightsArrivalPoint"].toString());
                    ticketsFull.setAirplaneName(jsonObject["AirplaneName"].toString());
                    ticketsFull.setAirplaneDescription(jsonObject["AirplaneDescription"].toString());
                    ticketsFull.setAirplaneMaxSizeCargo(jsonObject["AirplaneMaxSizeCargo"].toInt());
                    ticketsFull.setAirplaneMaxWeightCargo(jsonObject["AirplaneMaxWeightCargo"].toInt());
                    ticketsFull.setAirplaneMaxSeatPlaces(jsonObject["AirplaneMaxSeatPlaces"].toInt());
                    ticketsFull.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    ticketsFull.setTicketsBaggageAvailable(jsonObject["TicketsBaggageAvailable"].toInt() == 1);
                    ticketsFull.setBaggageName(jsonObject["BaggageName"].toString());
                    ticketsFull.setBaggageDescription(jsonObject["BaggageDescription"].toString());
                    ticketsFull.setBaggageWeight(jsonObject["BaggageWeight"].toInt());
                    ticketsFull.setBaggageSize(jsonObject["BaggageSize"].toInt());
                    ticketsFull.setTicketsSeatNumber(jsonObject["TicketsSeatNumber"].toInt());
                    ticketsFull.setTicketsIsDeleted(jsonObject["TicketsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(ticketsFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---TicketsFull

void NetworkAPIRequester::getAllTicketsTrunc(const std::function<void(QList<TicketsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsTrunc/TicketsTruncExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteTicketsTrunc(const std::function<void(QList<TicketsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsTrunc/TicketsTruncExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveTicketsTrunc(const std::function<void(QList<TicketsTrunc>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsTrunc/TicketsTruncExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<TicketsTrunc> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(TicketsTrunc(jsonObject["TicketsId"].toInt(), jsonObject["TicketsPrice"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["FlightsDepartureDate"].toString(), jsonObject["FlightsArrivalPoint"].toString(), jsonObject["FlightsLadder"].toInt(), jsonObject["TicketsBaggageAvailable"].toInt() == 1, jsonObject["BaggageName"].toString(), jsonObject["TicketsSeatNumber"].toInt(), jsonObject["TicketsIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchTicketsTrunc(const std::function<void (TicketsTrunc)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, TicketsTrunc ticketsTrunc)
{
    QNetworkRequest request(QUrl(this->url + "Tables/TicketsTrunc/TicketsTruncSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("SeatNumber", QString::number(ticketsTrunc.getTicketsSeatNumber()));

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        TicketsTrunc ticketsTrunc(0, 0, "", "", "", "", "", 0, false, "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    ticketsTrunc.setTicketsId(jsonObject["TicketsId"].toInt());
                    ticketsTrunc.setTicketsPrice(jsonObject["TicketsPrice"].toInt());
                    ticketsTrunc.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    ticketsTrunc.setClientLastName(jsonObject["ClientLastName"].toString());
                    ticketsTrunc.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    ticketsTrunc.setFlightsDepartureDate(jsonObject["FlightsDepartureDate"].toString());
                    ticketsTrunc.setArrivalPoint(jsonObject["FlightsArrivalPoint"].toString());
                    ticketsTrunc.setFlightsLadder(jsonObject["FlightsLadder"].toInt());
                    ticketsTrunc.setTicketsBaggageAvailable(jsonObject["TicketsBaggageAvailable"].toInt() == 1);
                    ticketsTrunc.setBaggageName(jsonObject["BaggageName"].toString());
                    ticketsTrunc.setTicketsSeatNumber(jsonObject["TicketsSeatNumber"].toInt());
                    ticketsTrunc.setTicketsIsDeleted(jsonObject["TicketsIsDeleted"].toInt() == 1);
            }

            callBackSuccess(ticketsTrunc);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---TicketsTrunc

void NetworkAPIRequester::getAllClientFull(const std::function<void(QList<ClientFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Views/ClientFull/ClientFullExtractAll.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientFull(jsonObject["ClientId"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["ClientMoney"].toInt(), jsonObject["ClientIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getDeleteClientFull(const std::function<void(QList<ClientFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Views/ClientFull/ClientFullExtractDelete.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientFull(jsonObject["ClientId"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["ClientMoney"].toInt(), jsonObject["ClientIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::getActiveClientFull(const std::function<void(QList<ClientFull>)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed)
{
    QNetworkRequest request(QUrl(this->url + "Views/ClientFull/ClientFullExtractActive.php"));

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        QList<ClientFull> list;

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    list.append(ClientFull(jsonObject["ClientId"].toInt(), jsonObject["ClientFirstName"].toString(), jsonObject["ClientLastName"].toString(), jsonObject["ClientPatronymic"].toString(), jsonObject["ClientPassportSeries"].toInt(), jsonObject["ClientPassportNumber"].toInt(), jsonObject["AccountLogin"].toString(), jsonObject["AccountPassword"].toString(), jsonObject["ClientMoney"].toInt(), jsonObject["ClientIsDeleted"].toInt() == 1));
            }

            callBackSuccess(list);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchClientFull(const std::function<void (ClientFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientFull clientFull)
{
    QNetworkRequest request(QUrl(this->url + "Vliews/ClientFull/ClientFullSearch.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("FirstName", clientFull.getClientFirstName());
    query.addQueryItem("LastName", clientFull.getClientLastName());
    query.addQueryItem("Patronymic", clientFull.getClientPatronymic());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        ClientFull clientFull(0, "", "", "", 0, 0, "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    clientFull.setClientId(jsonObject["ClientId"].toInt());
                    clientFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    clientFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    clientFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    clientFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    clientFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    clientFull.setAccountLogin(jsonObject["AccountLogin"].toString());
                    clientFull.setAccountPassword(jsonObject["AccountPassword"].toString());
                    clientFull.setClientMoney(jsonObject["ClientMoney"].toInt());
                    clientFull.setClientIsDeleted(jsonObject["ClientIsDeleted"].toInt() == 1);
            }

            callBackSuccess(clientFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}
void NetworkAPIRequester::searchByLoginClientFull(const std::function<void (ClientFull)> callBackSuccess, const std::function<void (unsigned int, QString, QString)> callBackFailed, ClientFull clientFull)
{
    QNetworkRequest request(QUrl(this->url + "Views/ClientFull/ClientFullSearchByLogin.php"));
    QUrlQuery query;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    query.addQueryItem("Login", clientFull.getAccountLogin());

    QNetworkReply *reply = networkAccessManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, this, [this, reply, callBackSuccess, callBackFailed]()
    {
        QByteArray byteArray;

        QJsonDocument jsonDocument;
        QJsonObject jsonObject;
        QJsonArray jsonArray;

        ClientFull clientFull(0, "", "", "", 0, 0, "", "", 0, false);

        if(reply->isFinished())
        {
            byteArray = reply->readAll();

            if(reply->error() != QNetworkReply::NoError)
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonDocument = QJsonDocument::fromJson(byteArray);

            if(!jsonDocument.isObject())
            {
                setErrnoState(reply->error(), byteArray);
                callBackFailed(reply->error(), reply->errorString(), getErrnoLine());
                return;
            }

            jsonObject = jsonDocument.object();

            jsonArray = jsonObject["records"].toArray();

            for(int counter = 0; counter < jsonArray.size(); ++counter)
            {
                    jsonObject = jsonArray.at(counter).toObject();

                    clientFull.setClientId(jsonObject["ClientId"].toInt());
                    clientFull.setClientFirstName(jsonObject["ClientFirstName"].toString());
                    clientFull.setClientLastName(jsonObject["ClientLastName"].toString());
                    clientFull.setClientPatronymic(jsonObject["ClientPatronymic"].toString());
                    clientFull.setClientPassportSeries(jsonObject["ClientPassportSeries"].toInt());
                    clientFull.setClientPassportNumber(jsonObject["ClientPassportNumber"].toInt());
                    clientFull.setAccountLogin(jsonObject["AccountLogin"].toString());
                    clientFull.setAccountPassword(jsonObject["AccountPassword"].toString());
                    clientFull.setClientMoney(jsonObject["ClientMoney"].toInt());
                    clientFull.setClientIsDeleted(jsonObject["ClientIsDeleted"].toInt() == 1);
            }

            callBackSuccess(clientFull);
            setErrnoState(0, "Success");
        }

        reply->close();
        reply->deleteLater();
    });
}

//---ClientFull

void NetworkAPIRequester::setErrno(unsigned char errnoCode){ this->error = errnoCode; }
void NetworkAPIRequester::setErrorLine(QString errnoLine){ this->errorLine = errnoLine; }
void NetworkAPIRequester::setErrnoState(unsigned char errnoCode, QString errnoLine)
{
    setErrno(errnoCode);
    setErrorLine(errnoLine);
}

unsigned char NetworkAPIRequester::getErrno() const{ return this->error; }

QString NetworkAPIRequester::getErrnoLine() const{ return this->errorLine;}
