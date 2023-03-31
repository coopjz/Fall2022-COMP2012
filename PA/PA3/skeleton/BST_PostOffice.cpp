//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_PostOffice.h"

// TODO: Constructors and Destructors

// TIP: root will be nullptr at first, and we'll add a node once we try to add a mail object.
BST_PostOffice::BST_PostOffice()
{
    root = nullptr;
}

BST_PostOffice_Node::BST_PostOffice_Node(Mail *mail)
{
    district = mail->getDistrict();
    mailman[mail->getAddressHash()].addMail(mail);
    right = nullptr;
    left = nullptr;
}

BST_PostOffice::~BST_PostOffice()
{
    delete root;
}

BST_PostOffice_Node::~BST_PostOffice_Node()
{
    delete right;
    delete left;
}

// TODO: Accessor functions.
BST_PostOffice *BST_PostOffice_Node::getLeftBST() const
{
    return left;
}

BST_PostOffice *BST_PostOffice_Node::getRightBST() const
{
    return right;
}

District BST_PostOffice_Node::getDistrict() const
{
    return district;
}

// TODO: Given a district, id and street name, find the mail object.
Mail *BST_PostOffice::find(District dist, int id, std::string streetName)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (dist == root->district)
    {
        return root->find(id, streetName);
    }
    else if (dist < root->district)
    {
        if (root->left == nullptr)
        {
            return nullptr;
        }
        return root->left->find(dist, id, streetName);
    }
    else
    {
        if (root->right == nullptr)
        {
            return nullptr;
        }
        return root->right->find(dist, id, streetName);
    }
    return nullptr;
}

Mail *BST_PostOffice_Node::find(int id, std::string streetName)
{
    for (int i = 0; i < HASH_MODULO; i++)
    {
        if (mailman[i].find(id, streetName) != nullptr)
        {
            return mailman[i].find(id, streetName);
        }
    }
    return nullptr;
}

// TODO: Given a district, id and street name, remove the mail object from the
// system.
bool BST_PostOffice::remove(District dist, int id, std::string streetName)
{
    if (root == nullptr)
    {
        return false;
    }
    if (dist == root->district)
    {
        return root->remove(id, streetName);
    }
    else if (dist < root->district)
    {
        if (root->left == nullptr)
        {
            return false;
        }
        return root->left->remove(dist, id, streetName);
    }
    else
    {
        if (root->right == nullptr)
        {
            return false;
        }
        return root->right->remove(dist, id, streetName);
    }
    return false;
}

bool BST_PostOffice_Node::remove(int id, std::string streetName)
{
    for (int i = 0; i < HASH_MODULO; i++)
    {
        if (mailman[i].remove(id, streetName))
            return true;
    }
    return false;
}

// TODO: Add mail to the system
void BST_PostOffice::addMail(Mail *mail)
{
    if (root == nullptr)
    {
        root = new BST_PostOffice_Node(mail);
    }
    else if (mail->getDistrict() == root->district)
    {

        root->addMail(mail);
    }
    else if (mail->getDistrict() < root->district)
    {
        if (root->left == nullptr)
        {
            root->left = new BST_PostOffice();
        }
        root->left->addMail(mail);
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = new BST_PostOffice();
        }
        root->right->addMail(mail);
    }
}

void BST_PostOffice_Node::addMail(Mail *mail)
{
    mailman[mail->getAddressHash()].addMail(mail);
}

// TODO: Given a district, print all of the data in it.
// TIP: Print style depends on type.
void BST_PostOffice::printDistrict(District dist, printType type) const
{
    if (root == nullptr)
    {
        return;
    }
    if (dist == root->district)
    {
        // std::cout << "BST Node for District: " << dist << std::endl;
        std::cout << "The District Mail Report for district " << dist << std::endl;
        root->print(type);
    }
    else if (dist < root->district)
    {
        if (root->left != nullptr)
            root->left->printDistrict(dist, type);
    }
    else
    {
        if (root->right != nullptr)
            root->right->printDistrict(dist, type);
    }
}

void BST_PostOffice_Node::print(printType type) const
{
    switch (type)
    {
    case printType::inorder:
    {
        for (int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl;
            mailman[i].printInOrder();
        }
        break;
    }
    case printType::preorder:
    {
        for (int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl;
            mailman[i].printPreOrder();
        }
        break;
    }
    case printType::postorder:
    {

        for (int i = 0; i < HASH_MODULO; i++)
        {
            std::cout << "For Mailman " << i << std::endl;
            mailman[i].printPostOrder();
        }
        break;
    }
    }
}

// TODO: Given a district and ID of the mailman, print all mail in it
// TIP: Print style depends on type - see the header file
void BST_PostOffice::printMailman(District district, int i, printType type) const
{
    if (root == nullptr)
    {
        return;
    }
    if (district == root->district)
    {
        root->printMailman(i, type);
    }
    else if (district < root->district)
    {
        root->left->printMailman(district, i, type);
    }
    else
    {
        root->right->printMailman(district, i, type);
    }
}

void BST_PostOffice_Node::printMailman(int i, printType type) const
{
    switch (type)
    {
    case printType::inorder:
    {
        mailman[i].printInOrder();
        break;
    }
    case printType::preorder:
    {
        mailman[i].printPreOrder();
        break;
    }
    case printType::postorder:
    {
        mailman[i].printPostOrder();
        break;
    }
    }
}

// TODO: Other print functions.
void BST_PostOffice::printInOrder() const
{
    // if (root == nullptr) {
    //         return;
    //     }
    //     root->left->printInOrder();
    //     std::cout <<"BST Node for District: "<< root->district << std::endl;
    //     for(int i = 0; i < HASH_MODULO; i++){
    //         root->mailman[i].printInOrder();
    //     }
    //     root->right->printInOrder();
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        root->left->printInOrder();
    }
    std::cout << "BST Node for District: " << root->district << std::endl;
    for (int i = 0; i < HASH_MODULO; i++)
        root->printMailman(i, printType::inorder);
    if (root->right != nullptr)
    {
        root->right->printInOrder();
    }
}

void BST_PostOffice::printPostOrder() const
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
    std::cout << "BST Node for District: " << root->district << std::endl;
    for (int i = 0; i < HASH_MODULO; i++)
        root->printMailman(i, printType::postorder);
}

void BST_PostOffice::printPreOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    std::cout << "BST Node for District: " << root->district << std::endl;
    for (int i = 0; i < HASH_MODULO; i++)
        root->printMailman(i, printType::preorder);
    if (root->left != nullptr)
    {
        root->left->printPreOrder();
    }
    if (root->right != nullptr)
    {
        root->right->printPreOrder();
    }
}