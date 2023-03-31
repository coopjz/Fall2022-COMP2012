//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_Mailman.h"

// TODO: Constructors and Destructors
BST_Mailman::BST_Mailman()
{
    root = nullptr;
}

BST_Mailman_Node::BST_Mailman_Node(Mail *mail)
{
    streetName = mail->getStreetName();
    mailPtr[currentMailsStored] = mail;
    currentMailsStored++;
    right = nullptr;
    left = nullptr;
}

BST_Mailman::~BST_Mailman()
{
    delete root;
}

BST_Mailman_Node::~BST_Mailman_Node()
{
    delete right;
    delete left;
    for (int i = 0; i < currentMailsStored; i++)
    {
        delete mailPtr[i];
    }
}

// TODO: Getters
std::string BST_Mailman_Node::getStreetName() const
{
    return streetName;
}

BST_Mailman *BST_Mailman_Node::getRightBST() const
{
    return right;
}

BST_Mailman *BST_Mailman_Node::getLeftBST() const
{
    return left;
}

// TODO add mail to the array mailPtr[] - NOTE: WE WILL NEVER ASK YOU TO
//  PUT TOO MANY MAILS. (a max of MAX_NUM_MAILS add_mail calls)
void BST_Mailman::addMail(Mail *mail)
{
    if (root == nullptr)
    {
        root = new BST_Mailman_Node(mail);
    }
    else
    {
        root->addMail(mail);
    }
}

void BST_Mailman_Node::addMail(Mail *mail)
{
    if (mail->getStreetName() == streetName)
    {
        mailPtr[currentMailsStored++] = mail;
    }
    else if (mail->getStreetName().compare(streetName) < 0)
    {
        if (left == nullptr)
        {
            left = new BST_Mailman();
        }
        left->addMail(mail);
    }
    else
    {
        if (right == nullptr)
        {
            right = new BST_Mailman();
        }
        right->addMail(mail);
    }
}

// TODO: Remove a mail, given its street name and ID
bool BST_Mailman::remove(int id, std::string streetName)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (streetName == root->streetName)
    {

        return root->remove(id);
    }
    else if (streetName.compare(root->streetName) < 0)
    {
        if (root->left == nullptr)
        {
            return false;
        }
        else
        {
            return root->left->remove(id, streetName);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            return false;
        }
        else
        {
            return root->right->remove(id, streetName);
        }
    }
    return false;
}

bool BST_Mailman_Node::remove(int id)
{
    for (int i = 0; i < currentMailsStored; i++)
    {
        if (mailPtr[i]->getId() == id)
        {
            delete mailPtr[i];
            mailPtr[i] = mailPtr[currentMailsStored - 1];
            mailPtr[currentMailsStored - 1] = nullptr;
            currentMailsStored--;
            return true;
        }
    }
    return false;
}

// TODO: Find a mail item, given its street name and ID
Mail *BST_Mailman::find(int id, std::string streetName)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (streetName == root->streetName)
    {
        return root->find(id);
    }
    else if (streetName.compare(root->getStreetName()) < 0)
    {
        if (root->left == nullptr)
        {
            return nullptr;
        }
        else
        {
            return root->left->find(id, streetName);
        }
    }
    else
    {
        if (root->right == nullptr)
            return nullptr;
        else
            root->right->find(id, streetName);
    }

    return nullptr;
}

Mail *BST_Mailman_Node::find(int id)
{
    for (int i = 0; i < currentMailsStored; i++)
    {
        if (mailPtr[i]->getId() == id)
        {
            return mailPtr[i];
        }
    }
    return nullptr;
}

// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        root->left->printInOrder();
    }
    root->print();
    if (root->right != nullptr)
    {
        root->right->printInOrder();
    }
}

void BST_Mailman::printPostOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        root->left->printPostOrder();
    }
    if (root->right != nullptr)
    {
        root->right->printPostOrder();
    }
    root->print();
}

void BST_Mailman::printPreOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    root->print();
    if (root->left != nullptr)
    {
        root->left->printPreOrder();
    }
    if (root->right != nullptr)
    {
        root->right->printPreOrder();
    }
}

void BST_Mailman_Node::print() const
{
    std::cout << "BST Node for Street: " << streetName << std::endl;
    for (int i = 0; i < currentMailsStored; ++i)
    {
        if (mailPtr[i] != nullptr)
        {
            mailPtr[i]->printMail();
        }
    }
}
