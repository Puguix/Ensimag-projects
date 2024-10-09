import pandas as pd
import datetime
import numpy as np
import json

####################################################
################ TO BE MODIFIED ####################
####################################################
#Files Path
prices_df = pd.read_excel(r"C:\Users\othma\Downloads\DonneesGPS2024.xlsx", sheet_name="ClosePrice")[["Date", "DAX", "BOVESPA", "TSX300"]]
returns_df = pd.read_excel(r"C:\Users\othma\Downloads\DonneesGPS2024.xlsx", sheet_name="CloseRet")[["Date", "DAX", "BOVESPA", "TSX300"]]
taux_change_prices_df = pd.read_excel(r"C:\Users\othma\Downloads\DonneesGPS2024.xlsx", sheet_name="XFORPrice")[["Date", "XBRL", "XCAD"]]
taux_change_returns_df = pd.read_excel(r"C:\Users\othma\Downloads\DonneesGPS2024.xlsx", sheet_name="XFORRet")[["Date", "XBRL", "XCAD"]]
interet_df = pd.read_excel(r"C:\Users\othma\Downloads\DonneesGPS2024.xlsx", sheet_name="TauxInteret")[["Date", "REUR", "RBRL", "RCAD"]]

#First available excel date
incept_date = prices_df.iloc[0].Date


present_date = datetime.datetime(year=2005, month=6, day=30)
beg_simu_date = datetime.datetime(year=2005, month=1, day=4)  #T0
maturity_date = datetime.datetime(year=2010, month=1, day=4)
maturity_date_int = np.busday_count(beg_simu_date.date(), maturity_date.date()) #maturity in int

#Constation dates
consta_dates = [datetime.datetime(year=2006, month=1, day=4),
                datetime.datetime(year=2007, month=1, day=4),
                datetime.datetime(year=2008, month=1, day=4),
                datetime.datetime(year=2009, month=1, day=5)]

nb_dates = 260

####################################################
################ DON'T MODIFY ####################
####################################################
if(any(prices_df.Date == present_date)):
    prices_df = prices_df.merge(taux_change_prices_df, on="Date", how="inner")
    returns_df = returns_df.merge(taux_change_returns_df, on="Date", how="inner")


    if(present_date - datetime.timedelta(days=2*252) > incept_date):
        incept_date = present_date - datetime.timedelta(days=2*252)

    returns_df = returns_df[(returns_df["Date"] > incept_date) & (returns_df["Date"] <= present_date)].fillna(method='ffill').fillna(method='bfill')
    prices_df = prices_df[(prices_df["Date"] <= present_date)].fillna(method='ffill').fillna(method='bfill')
    interet_df = interet_df[(interet_df["Date"] == present_date)]
    interet_list = list(interet_df.iloc[0])[1::]

    cor_returns = returns_df[["DAX", "BOVESPA", "TSX300", "XBRL", "XCAD"]].corr()
    vol = list(returns_df[["DAX", "BOVESPA", "TSX300", "XBRL", "XCAD"]].std())

    prices_df = prices_df[(prices_df["Date"].isin(consta_dates)) | (prices_df["Date"] == present_date) | (prices_df["Date"] == beg_simu_date)]


    dates_int = [0] #dates in path matrix to be sent to the pricer (from t0 to present date)
    consta_dates_int = [0] #all of constation dates in int format

    for date in consta_dates:
        date_int = np.busday_count(beg_simu_date.date(), date.date())
        consta_dates_int += [date_int]
        if(date < present_date):
            dates_int += [date_int]

    if(np.busday_count(beg_simu_date.date(), present_date.date()) not in dates_int):
        dates_int += [np.busday_count(beg_simu_date.date(), present_date.date())]

    consta_dates_int += [maturity_date_int]
    dates_int = sorted(dates_int)

    prices_df["BOVESPA"] = prices_df["BOVESPA"]*prices_df["XBRL"]
    prices_df["TSX300"] = prices_df["TSX300"]*prices_df["XCAD"]

    for col in ["XBRL", "XCAD"]:
        temp_dates = np.exp(interet_df["R" + col[1::]].iloc[0]*np.array(dates_int)/nb_dates)
        prices_df[col] = prices_df[col].multiply(temp_dates)

else:
    print("Données pas dispo pour ce jour")


print("debug")