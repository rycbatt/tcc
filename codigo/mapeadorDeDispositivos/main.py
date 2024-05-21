from typing import Dict, Optional


class Dispositivo:
    def __init__(self, mac: str, conhecidos: Optional[Dict[str, int]] = None):
        self.mac: str = mac
        self.conhecidos: Dict[str, int] = conhecidos if conhecidos is not None else {}

    def adicionar_conhecido(self, mac_conhecido: str, rssi: int) -> None:
        """Adiciona ou atualiza o RSSI de um dispositivo conhecido."""
        self.conhecidos[mac_conhecido] = rssi

    def remover_conhecido(self, mac_conhecido: str) -> None:
        """Remove um dispositivo conhecido pelo seu MAC, se existir."""
        if mac_conhecido in self.conhecidos:
            del self.conhecidos[mac_conhecido]

    def obter_rssi(self, mac_conhecido: str) -> int:
        """Retorna o RSSI de um dispositivo conhecido, se existir."""
        return self.conhecidos.get(mac_conhecido, None)

    def listar_conhecidos(self) -> Dict[str, int]:
        """Retorna uma lista de todos os dispositivos conhecidos e seus RSSI."""
        return self.conhecidos.items()



def pega_dispositivos():

    arquivo = 

    for dispositivo in 

    return dispositivos




dispositivos = pega_dispositivos()
for dispositivo in dispositivos:
    dispositivo.id
    dispositivo.conhecidos