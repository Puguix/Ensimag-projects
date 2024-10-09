import pandas as pd
import datetime
import numpy as np
import json


path = "../Data/DonneesGPS2024.xlsx"

#starting date =  T0
#end_date = Tc
#present_date = the date you want to get price / deltas
def load_data_date(starting_date, present_date, end_date):
    prices_df = pd.read_excel(path, sheet_name="ClosePrice")[["Date", "DAX", "BOVESPA", "TSX300"]]
    returns_df = pd.read_excel(path, sheet_name="CloseRet")[["Date", "DAX", "BOVESPA", "TSX300"]]
    taux_change_prices_df = pd.read_excel(path, sheet_name="XFORPrice")[["Date", "XBRL", "XCAD"]]
    taux_change_returns_df = pd.read_excel(path, sheet_name="XFORRet")[["Date", "XBRL", "XCAD"]]
    interet_df = pd.read_excel(path, sheet_name="TauxInteret")[["Date", "REUR", "RBRL", "RCAD"]]

    incept_date = prices_df.iloc[0].Date

    consta_dates = []
    maturity_date_int = np.busday_count(starting_date.date(), end_date.date()) #maturity in int

    if starting_date == datetime.datetime(year=2000, month=7, day=5):

        consta_dates = [datetime.datetime(year=2001, month=7, day=3),
                 datetime.datetime(year=2002, month=7, day=2),
                 datetime.datetime(year=2003, month=7, day=2),
                 datetime.datetime(year=2004, month=7, day=2)]

    if starting_date == datetime.datetime(year=2005, month=1, day=4):
        
        consta_dates = [datetime.datetime(year=2006, month=1, day=4),
                 datetime.datetime(year=2007, month=1, day=4),
                 datetime.datetime(year=2008, month=1, day=4),
                 datetime.datetime(year=2009, month=1, day=5)]
        
    if starting_date == datetime.datetime(year=2009, month=1, day=5):

        consta_dates = [datetime.datetime(year=2010, month=1, day=4),
                datetime.datetime(year=2011, month=1, day=4),
                datetime.datetime(year=2012, month=1, day=4),
                datetime.datetime(year=2013, month=1, day=4)]
    
    nb_dates = 260

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
        cor_returns = cor_returns.values.tolist()
        vol = list(returns_df[["DAX", "BOVESPA", "TSX300", "XBRL", "XCAD"]].std())
        prices_df = prices_df[(prices_df["Date"].isin(consta_dates)) | (prices_df["Date"] == present_date) | (prices_df["Date"] == starting_date)]


        dates_int = [0] #dates in path matrix to be sent to the pricer (from t0 to present date)
        consta_dates_int = [0] #all of constatation dates in int format

        for date in consta_dates:
            date_int = np.busday_count(starting_date.date(), date.date())
            print(date_int)
            consta_dates_int += [date_int]
            if(date < present_date):
                dates_int += [date_int]

        if(np.busday_count(starting_date.date(), present_date.date()) not in dates_int):
            dates_int += [np.busday_count(starting_date.date(), present_date.date())]

        consta_dates_int += [maturity_date_int]
        #Conversion en int pour Json
        consta_dates_int = [int(date) for date in consta_dates_int]
        maturity_date_int = int(maturity_date_int)
        dates_int = sorted(dates_int)
        prices_df["BOVESPA"] = prices_df["BOVESPA"]*prices_df["XBRL"]
        prices_df["TSX300"] = prices_df["TSX300"]*prices_df["XCAD"]

        for col in ["XBRL", "XCAD"]:
            temp_dates = np.exp(interet_df["R" + col[1::]].iloc[0]*np.array(dates_int)/nb_dates)
            prices_df[col] = prices_df[col].multiply(temp_dates)

    return prices_df, cor_returns, vol, interet_list, maturity_date_int, consta_dates_int


##################################################
#######################TEST#######################
##################################################
present_date = datetime.datetime(year=2005, month=6, day=30)
beg_simu_date = datetime.datetime(year=2005, month=1, day=4)  #T0
maturity_date = datetime.datetime(year=2010, month=1, day=4)  #Tc


if __name__ == "__main__":
    prices_df, cor_returns, vol, interet_list, maturity_date_int, consta_dates_int = load_data_date(beg_simu_date, present_date, maturity_date)

    json_data = {
    "InterestRates": interet_list,
    "Volatilities_X": vol[3::],
    "Volatilities_Assets": vol[0::2],
    "Correlations": cor_returns,
    "constatationDates": consta_dates_int,
    "maturity": maturity_date_int
    }

    with open("data.json", "w") as outfile:
        json.dump(json_data, outfile, indent=4)