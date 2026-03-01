# Philosophers

Résolution du problème classique des philosophes qui dînent (threads & mutexes).

## 🚀 Démarrage rapide

### Compilation
\`\`\`bash
make
\`\`\`

### Utilisation
\`\`\`bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
\`\`\`

Exemple :
\`\`\`bash
./philo 5 800 200 200
\`\`\`

## 📚 Fonctionnalités

- Simulation multi-threaded de philosophes
- Détection de deadlock et starvation
- Logs d'événements précis

## 🛠️ Commandes

\`\`\`bash
make              # Compiler
make clean        # Nettoyer
make re           # Recompiler
\`\`\`

## 🔧 Technologies

- C
- POSIX Threads
- Mutexes
