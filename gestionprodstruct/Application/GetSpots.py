import pandas as pd
import numpy as np


def get_spots(date):
    df = pd.read_excel("./Data/FinalPrices.xlsx") 
    df['Date'] = pd.to_datetime(df['Date'])
    df.set_index('Date', inplace=True)
    return df.loc[date]
