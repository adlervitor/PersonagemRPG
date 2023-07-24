#include <iostream>
#include <vector>
#include <cstdlib> // Para a função rand()
#include <ctime>   // Para inicializar a semente do gerador de números aleatórios
#include <Windows.h> // Para o SetConsoleOutputCP(CP_UTF8)
#include <algorithm> // Para o std::all_of

using namespace std;

// ================================= Criador de Fichas para RPG de Sobrevivência Zumbi =========================================
// Este programa permite criar fichas de personagens para um RPG de sobrevivência em um mundo pós apocalíptico.
// Os personagens têm nomes, backgrounds, habilidades, atributos e equipamentos que os ajudarão em suas aventuras.
// Cada personagem escolherá duas habilidades, uma arma inicial e um item de acordo com o background desejado.
// Para mais, cada um receberá uma lanterna para ajudar em sua jornada.
// Os atributos dos personagens e das armas serão escolhidos baseados em jogadas de dados de 10 lados e 6 lados respectivamente.


// "Called by the grave - O chamado da cova"
// No mundo pós-Apocalipse Zumbi, os jogadores enfrentam um cenário devastado pela epidemia que transformou amigos e familiares em 
// criaturas sedentas de sangue. Em "Called by the grave", eles devem formar alianças, buscar recursos escassos 
// e enfrentar decisões cruciais para garantir a sobrevivência. A cada passo, suas escolhas moldarão o destino dos personagens e do mundo 
// que conheciam. Aventuras perigosas aguardam os sobreviventes, enquanto eles lutam para encontrar esperança em meio à escuridão e caos.


// Função para simular um dado, recebe o valor máximo do dado como parâmetro.
int jogarDado(int num)
{ 
    int result = rand() % num + 1;
    return result;
}

// Classe Equipamento para representar um equipamento que o personagem pode usar.
class Equipamento
{
public:
    string tipo;
    int forca, precisao, capacidade, durabilidade;
};

// Classe Item para representar um item que o personagem pode carregar.
class Item
{
public:
    string nome;
    int quantidade;
};

// Classe Personagem para representar um personagem do RPG.
class Personagem
{
public:
    string nome;
    string background;
    vector<string> habilidades;
    vector<Equipamento> equipamentos;
    vector<Item> itens;
    int hp, forca, destreza, inteligencia, carisma, nivel;

    // Função para adicionar o equipamento à ficha
    void adicionarEquip()
    { 
        Equipamento equipamento;

        cout << "Tipo da arma (Ex: Pistola, Metralhadora, Fuzil de atirador): " << endl;
        getline(cin, equipamento.tipo);

        {
            cout << "Background inválido. " << endl;
            getline(cin, equipamento.tipo);
        }

        srand(time(0));

        equipamento.forca = jogarDado(6);
        equipamento.precisao = jogarDado(6);
        equipamento.capacidade = jogarDado(6);
        equipamento.durabilidade = jogarDado(6);

        cout << "O dado foi jogado e os atributos da(o) " << equipamento.tipo << " são: " << endl;
        cout << "Força: " << equipamento.forca << endl;
        cout << "Precisão: " << equipamento.precisao << endl;
        cout << "Capacidade: " << equipamento.capacidade << endl;
        cout << "Durabilidade: " << equipamento.durabilidade << endl;

        equipamentos.push_back(equipamento);
        cout << endl;
    }

    // Função para adicionar a lanterna
    void adicionarLanterna()
    { 
        Equipamento lanterna;
        lanterna.tipo = "Lanterna";
        equipamentos.push_back(lanterna);

        cout << "Você recebeu uma lanterna!" << endl;

        cout << endl;
    }

    // Função para adicionar itens
    void adicionarItem()
    { 
        Item item;

        cout << "Nome do item: " << endl;
        getline(cin, item.nome);

        {
            cout << "Background inválido. " << endl;
            getline(cin, item.nome);
        }

        int quantidade;
        cout << "Digite a quantidade: " << endl;
        cin >> quantidade;
        // Loop para garantir que o usuário coloque um inteiro
        while (cin.fail() || quantidade < 0)
        {
            cout << "Quantidade inválida. Por favor, insira um número inteiro positivo." << endl;
            cin.clear();               // Limpa o estado de erro
            cin.ignore(INT_MAX, '\n'); // Ignora o restante da entrada inválida até a próxima linha

            cout << "Digite a quantidade: " << endl;
            cin >> quantidade;
        }

        item.quantidade = quantidade;

        itens.push_back(item);

        cout << item.nome << " adicionado(a) com sucesso!" << endl;

        cout << endl;
    }

    // Função para remover equipamentos
    void removerEquip(int num)
    {  
        equipamentos.erase(equipamentos.begin() + num);
    }

    // Função para remover itens
    void removerItem(int num)
    {
        itens.erase(itens.begin() + num);
    }

    // Função para exibir a ficha
    void exibirFicha()
    {
        cout << "Nome: " << nome << endl;
        cout << "Background: " << background << endl;

        cout << "Habilidades: " << endl;
        for (size_t i = 0; i < habilidades.size(); i++)
        {
            cout << "" << i + 1 << ". " << habilidades[i] << endl;
        }

        cout << "Nível: " << nivel << endl;
        cout << "Pontos de vida: " << hp << endl;
        cout << "Pontos de força: " << forca << endl;
        cout << "Pontos de destreza: " << destreza << endl;
        cout << "Pontos de inteligência: " << inteligencia << endl;
        cout << "Pontos de carisma: " << carisma << endl;

        cout << "Equipamentos: " << endl;
        for (size_t i = 0; i < equipamentos.size(); i++)
        {
            cout << "" << i + 1 << ". " << equipamentos[i].tipo << endl;
        }

        cout << "Itens: " << endl;
        for (size_t i = 0; i < itens.size(); i++)
        {
            cout << "" << i + 1 << ". " << itens[i].nome << " - Qtd: " << itens[i].quantidade << endl;
        }

        cout << endl;
    }
};

int main()
{
     // Consertar acentos no console
    SetConsoleOutputCP(CP_UTF8);

    vector<Personagem> personagens;

    int opcao = 0;
    // O loop roda até o usuário selecionar o número 3
    while (opcao != 3)
    {
        cout << "===== Bem-vindo ao criador de fichas! =====" << endl;
        cout << "Selecione uma opção: " << endl;
        cout << "1. Criar ficha de personagem" << endl;
        cout << "2. Exibir fichas de personagens" << endl;
        cout << "3. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;
        // Loop para garantir que o usuário coloque um inteiro
        if (cin.fail())
        {
            cout << "Entrada inválida. Por favor, insira um número inteiro." << endl;
            cin.clear();               // Limpa o estado de erro
            cin.ignore(INT_MAX, '\n'); // Ignora o restante da entrada inválida até a próxima linha
            continue;                  // Volta ao início do loop para pedir a escolha novamente
        }

        cin.ignore();

        switch (opcao)
        {
        case 1:
        {
            // Cria uma instância da classe personagem
            Personagem personagem;

            cout << "===== Crie o seu sobrevivente =====" << endl;

            cout << "Digite o nome do seu personagem: " << endl;
            getline(cin, personagem.nome);

            {
                cout << "Nome inválido. Por favor, digite um nome válido: " << endl;
                getline(cin, personagem.nome);
            }

            cout << endl;

            cout << "Digite o seu background: " << endl;
            getline(cin, personagem.background);

            {
                cout << "Background inválido. " << endl;
                getline(cin, personagem.background);
            }

            cout << endl;

            cout << "Habilidades do personagem (2): " << endl;
            // Limita a quantidade de habilidades do personagem
            while (personagem.habilidades.size() < 2)
            { 
                string habilidade;
                cout << "Habilidade " << personagem.habilidades.size() + 1 << ": ";
                getline(cin, habilidade);
                personagem.habilidades.push_back(habilidade);
            }

            cout << endl;

            srand(time(0));
            // Decide aleatoriamente os atributos do personagem com um limite máximo de 10
            personagem.hp = jogarDado(10) * 10;
            personagem.forca = jogarDado(10);
            personagem.destreza = jogarDado(10);
            personagem.inteligencia = jogarDado(10);
            personagem.carisma = jogarDado(10);
            personagem.nivel = 1;
            
            cout << "O dado foi jogado e seus atributos são: " << endl;
            cout << "Pontos de vida: " << personagem.hp << endl;
            cout << "Pontos de força: " << personagem.forca << endl;
            cout << "Pontos de destreza: " << personagem.destreza << endl;
            cout << "Pontos de inteligência: " << personagem.inteligencia << endl;
            cout << "Pontos de carisma: " << personagem.carisma << endl;

            cout << endl;

            cout << "===== Escolha sua arma inicial =====" << endl;
            // Chama a função que adiciona o equipamento
            personagem.adicionarEquip();
            // Chama a função que adiciona a lanterna
            personagem.adicionarLanterna();

            cout << "===== Baseado em seu background, escolha um item pessoal =====" << endl;
            // Chama a função que adiciona o item inicial
            personagem.adicionarItem();

            cout << "Ficha criada com sucesso!" << endl;
            // Salva o personagem no vetor personagens
            personagens.push_back(personagem);

            cout << endl;
            break;
        }

        case 2:
        {
            if (personagens.empty())
            {
                cout << "Não há fichas de personagens criadas." << endl;
            }
            else
            {
                cout << "===== Escolha o personagem (Digite um número) =====" << endl;

                int escolhaPersonagem;
                size_t i;
                // Itera o vetor de personagens e exibe o nome de cada um
                for (i = 0; i < personagens.size(); i++)
                {
                    cout << "" << i + 1 << ". " << personagens[i].nome << endl;
                };

                cin >> escolhaPersonagem;
                escolhaPersonagem--;
                // Chama a função exibirFicha usando o índice oferecido pelo usuário
                personagens[escolhaPersonagem].exibirFicha();

                int opcaoItens;
                cout << "1. Adicionar Equipamento" << endl;
                cout << "2. Adicionar Item" << endl;
                cout << "3. Remover Equipamento" << endl;
                cout << "4. Remover Item" << endl;
                cout << "5. Voltar" << endl;
                cin >> opcaoItens;

                cin.ignore();

                if (cin.fail())
                {
                    cout << "Entrada inválida. Por favor, insira um número inteiro." << endl;
                    cin.clear();               // Limpa o estado de erro
                    cin.ignore(INT_MAX, '\n'); // Ignora o restante da entrada inválida até a próxima linha
                    continue;                  // Volta ao início do loop para pedir a escolha novamente
                }

                switch (opcaoItens)
                {
                case 1:
                {
                    // Chama a função adicionarEquip usando o índice oferecido pelo usuário
                    personagens[escolhaPersonagem].adicionarEquip();
                    break;
                }
                case 2:
                {
                    // Chama a função adicionarItem usando o índice oferecido pelo usuário
                    personagens[escolhaPersonagem].adicionarItem();
                    break;
                }
                case 3:
                {
                    int indiceEquip;
                    cout << "Digite o número do equipamento que deseja remover: " << endl;

                    for (i = 0; i < personagens[escolhaPersonagem].equipamentos.size(); i++)
                    {
                        cout << "" << i + 1 << ". " << personagens[escolhaPersonagem].equipamentos[i].tipo << endl;
                    };

                    cin >> indiceEquip;
                    cin.ignore();
                    // Chama a função removerEquip usando o índice oferecido pelo usuário
                    personagens[escolhaPersonagem].removerEquip(indiceEquip);

                    break;
                }
                case 4:
                {
                    int indiceItem;
                    cout << "Digite o número do item que deseja remover: " << endl;

                    for (i = 0; i < personagens[escolhaPersonagem].itens.size(); i++)
                    {
                        cout << "" << i + 1 << ". " << personagens[escolhaPersonagem].itens[i].nome << endl;
                    };

                    cin >> indiceItem;
                    cin.ignore();
                    // Chama a função removerItem usando o índice oferecido pelo usuário
                    personagens[escolhaPersonagem].removerItem(indiceItem);

                    break;
                }
                case 5:
                {
                    cout << "Voltando para o menu." << endl;
                    break;
                }
                default:
                {
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
                }
                }
            }
            break;
        }

        case 3:
        {
            cout << "Encerrando o programa." << endl;
            break;
        }

        default:
        {
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }
        }
    }

    return 0;
}
