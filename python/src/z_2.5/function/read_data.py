import pandas as pd


def read_excel(path: str):
    if path:
        return pd.read_excel(path)
    return None


def read_html(url: str):
    if url:
        return pd.read_html(url)
    return None
